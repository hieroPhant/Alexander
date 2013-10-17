#ifndef AlexanderNode_h
#define AlexanderNode_h

#include <memory>
//#include <mutex>

//locking should be safe, but will block
//look into using std::timed_mutex and std::lock to avoid blocking

namespace alex {

    template<typename LINK, bool IN> ArcList;

    template<typename LINK>
    struct Linker {
        //An element of the linked list managed by ArcList. Contains
        //a pointer back to each owning ArcList, along with pointers
        //to subsequent elements of each linked list. Stores a LINK.
        //This class should be considered an implementation detail of
        //ArcList. It is not nested inside ArcList because its type 
        //should not be specific to either input or output ArcLists.
        ArcList<LINK, true>* target;
        ArcList<LINK, false>* source;
        //std::mutex ptr_mutex;
        Linker* next_input;
        Linker* next_output;
        LINK link;

        //Only these constructors are called. The default constructor is fine.
        template<typename... ARGS> 
        Linker(ArcList<LINK,false>& from, ArcList<LINK,true>& to, ARGS&&... args) 
            : target(&to), source(&from), 
              next_input(nullptr), next_output(nullptr), 
              link(std::forward<ARGS>(args)...) {}

        template<typename... ARGS>
        Linker(ArcList<LINK,true>& to, ArcList<LINK,false>& from, ARGS&&... args) 
            : Linker(from, to, std::forward<ARGS>(args)...) {}
    };


    template<typename LINK, bool IN>
    class ArcList {
        //The data structure underlying the node in a directed graph. It stores
        //the links in a linked list. Each element of that list is shared with
        //another Node's ArcList. Since the elements are never moved in memory between
        //creation and destruction, they represent a safe way to send messages
        //between nodes. Because input and output ArcLists have different types, 
        //it is impossible to make a link between two input or two output ArcLists.
        class iterator;

        //std::mutex arclist_mutex;
        Linker<LINK>* first_link;

        bool clone(const ArcList& model) {
            //For each link in 'model', create a matching link in 'this'.
            //If an analagous link already exists, leave it. Otherwise,
            //use LINK's copy constructor.
            //std::lock_guard<std::mutex> lock(model.arclist_mutex);
            for(auto iter=model.begin(); bool(iter); ++iter) {
                //iter->ptr_mutex.lock();
                if(iter.other()) link(*iter.other(), iter->link);
                //iter->ptr_mutex.unlock();
            }
        }
        void join(Linker<LINK>* x) {
            //Insert the given link at the front of the linked list,
            //and set its 'me' pointer.
            iterator iter(x);
            //std::lock_guard<std::mutex> lock(arclist_mutex);
            iter.me() = this;
            iter.next() = first_link;
            first_link = x;
        }
        void clean(iterator iter) {
            //Set the given link's 'me' pointer to null, and test whether the other
            //ArcList has done the same. If both ArcList pointers are now null, then 
            //delete the Linker instead. If not, call 'unlink' for that partner, which
            //will in turn call 'clean' again.
            typedef typename ArcList<LINK, not IN>::iterator matching_iterator_type;
            //iter->ptr_mutex.lock();
            iter.me() = nullptr;
            auto linker_ptr = &(*iter);
            auto other_ptr = iter.other();
            if(iter.other() == nullptr) {
                //iter->ptr_mutex.unlock();
                delete linker_ptr;
            }
            else {
                //other.arclist_mutex.lock();
                //iter->ptr_mutex.unlock();
                iter.other()->unlink([linker_ptr](matching_iterator_type matching_iter) {
                    return linker_ptr == &(*matching_iter); 
                });
            }
        }
        template<typename PREDICATE>
        void unlink(PREDICATE p) {
            //Find the first link for which the given predicate is true, and
            //alter the linked list to skip over it. Then call 'clean' to safely
            //destroy the Linker. 'unlink' is mutually recursive with 'clean'.
            auto iter = begin();
            if(p(iter)) first_link = iter.next();
            else {
                iter = trail_search(iter, [&other](iterator it) {
                    //std::lock_guard<std::mutex> lock(it->ptr_mutex);
                    return it.other() == &other; });
                if(!bool(iter)) return;
                auto trail = iter++;
                trail.next() = iter.next();
            }
            //arclist_mutex.unlock(); //originally locked by caller
            clean(iter);
        }
        template<typename PREDICATE>
        iterator trail_search(iterator iter, PREDICATE p) {
            //Find the first Linker that satisfies the given predicate, and
            //return an iterator to the preceding element. If no links satisfy
            //the predicate, return a null iterator;
            auto trail = iter++;
            if(!bool(iter)) return iter; 
            else if(f(iter)) return trail;
            else return trail_search(iter, p);
        }
        iterator begin() { return iterator(first_link); }
        
    public:
        ArcList() : first_link(nullptr) {}
        ArcList& ArcList(const ArcList& rhs) : ArcList() { clone(rhs); }
        ArcList& operator=(const ArcList& rhs) {
            if(&rhs != this) {
                unlink_all();
                clone(rhs);
            }
            return *this;
        }
        ~ArcList() { unlink_all(); }

        template<typename FUNCTION> FUNCTION for_each(FUNCTION f) const {
            //Call the given function or functor on each LINK.
            for(auto iter=begin(); bool(iter); ++iter)
                f(iter->link);
            return f;
        }

        template<typename... ARGS> 
        bool link(ArcList<LINK, not IN>& other, ARGS&&... args) {
            //After verifying that such a link does not already exist, construct
            //the new Linker object and call 'join' for 'this' and 'other'.
            if(linked_to(other)) return false;
            auto linker = new Linker(*this, other, std::forward<ARGS>(args)...);
            join(linker);
            other.join(linker);
        }
        void unlink(ArcList<LINK, not IN>& other) {
            //If a link exists to 'other', destroy it. 
            //arclist_mutex.lock(); //gets unlocked inside unlink delegate
            unlink([&other](iterator iter) { 
                //std::lock_guard<std::mutex> lock(iter->ptr_mutex);
                return iter.other() == &other; 
            });
        }
        void unlink_all() {
            //arclist_mutex.lock();
            auto iter = begin();
            first_link = nullptr;
            //arclist_mutex.unlock();
            for(; bool(iter); ++iter) clean(iter);
        }

        bool linked_to(const ArcList<LINK, not IN>& other) const {
            //Return true if a link to 'other' exists.
            //std::lock_guard<std::mutex> lock(arclist_mutex);
            return bool(trail_search(iterator(first_link), [other](iterator iter) {
                //std::lock_guard<std::mutex> lock(iter->ptr_mutex);
                return iter.other() == &other; }));
        }
        size_t size() const {
            //Count the current number of links.
            size_t count = 0;
            //std::lock_guard<std::mutex> lock(arclist_mutex);
            for_each([&count](const Linker<LINK>&) { ++count; });
            return count;
        }
    };


    template<typename LINK, bool IN>
    class ArcList<LINK, IN>::iterator {
        //This class knows how to iterate over an ArcList, choosing the correct
        //pointer-to-next each time (each element has two such pointers, since each
        //element is shared between two ArcLists). It also knows which 
        //pointer-to-ArcList is which. 
        Linker<LINK>* current;

        Linker<LINK>*& next_impl(std::true_type) { return current->next_input; }
        Linker<LINK>*& next_impl(std::false_type) { return current->next_output; }

        ArcList<LINK, not IN>* list_ref(std::true_type) { return current->source; }
        ArcList<LINK, not IN>* list_ref(std::false_type) { return current->target; }

    public:
        iterator() : current(nullptr) {}
        explicit iterator(Linker<LINK>* linker_ptr) : current(linker_ptr) {}

        explicit operator bool() const { return current; }
        iterator& operator++() { current = next(); return *this; }
        iterator operator++(int) { auto temp = *this; current = next(); return temp; }

        Linker<LINK>& operator*() { return *current; }
        Linker<LINK>* operator->() { return current; }

        Linker<LINK>*& next() { return next_impl(IN); }
        ArcList<LINK, not IN>* other() { return list_ref(IN); }
        ArcList<LINK, not IN>*& me() { return list_ref(not IN); }
    };


    template<typename LINK>
    struct rawNode { 
        ArcList<LINK,true> inputs; 
        ArcList<LINK,false> outputs; 
    };


    template<typename LINK>
    class Node {
        //An abstraction layer over rawNode. The abstraction considers each Node to 
        //have control and visibility over only its inputs. This reflects a mathematical
        //function. A Node object can be thought of as a safe reference or handle to a pair
        //of ArcLists (a rawNode). This way it can be passed around and stored more easily.
        //If you want to copy by value, use 'mirror' to mimic the inputs of another Node.
        //Output links can still be accessed via 'for_outputs' - this is necessary to send
        //data - but they cannot be created or destroyed.
        
        //unique_ptr would require deletion of copy ctor and assignment op
        std::shared_ptr< rawNode<LINK> > links;

    public:
        Node() : links(new rawNode<LINK>()) {}

        template<typename FUNCTION>
        FUNCTION for_inputs(FUNCTION f) const { return links->inputs.for_each(f); }
        template<typename FUNCTION>
        FUNCTION for_outputs(FUNCTION f) const { return links->outputs.for_each(f); }

        template<typename... ARGS> bool link(Node& source, ARGS&&... args) {
            return links->inputs.link(source.links->outputs, std::forward<ARGS>(args)...);
        }
        void mirror(const Node& other) { links->inputs = other.links->inputs; }
        void unlink(const Node& source) { links->inputs.unlink(source.links->outputs); }
        void unlink_all() { links->inputs.unlink_all(); }
        
        bool linked_to(const Node& other) const { 
            return links->inputs.linked_to(other.links->outputs); 
        }
        size_t size() const { return links->inputs.size(); }
    };
} 

#endif

