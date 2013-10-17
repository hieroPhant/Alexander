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
        ArcList<LINK, true>* target;
        ArcList<LINK, false>* source;
        //std::mutex ptr_mutex;
        Linker* next_input;
        Linker* next_output;
        LINK link;

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
        class iterator;

        //std::mutex arclist_mutex;
        Linker<LINK>* first_link;

        bool clone(const ArcList& model) {
            //std::lock_guard<std::mutex> lock(model.arclist_mutex);
            for(auto iter=model.begin(); bool(iter); ++iter) {
                //iter->ptr_mutex.lock();
                if(iter.other()) link(*iter.other(), iter->link);
                //iter->ptr_mutex.unlock();
            }
        }
        void join(Linker<LINK>* x) {
            iterator iter(x);
            //std::lock_guard<std::mutex> lock(arclist_mutex);
            iter.me() = this;
            iter.next() = first_link;
            first_link = x;
        }
        void clean(iterator iter) {
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
            auto iter = begin();
            if(p(iter)) first_link = iter.next();
            else {
                iter = trail_search(iter, [&other](iterator it) {
                    //std::lock_guard<std::mutex> lock(it->ptr_mutex);
                    return it.other() == &other; });
                auto trail = iter++;
                trail.next() = iter.next();
            }
            //arclist_mutex.unlock(); //originally locked by caller
            clean(iter);
        }
        template<typename PREDICATE>
        iterator trail_search(iterator iter, PREDICATE p) {
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
            for(auto iter=begin(); bool(iter); ++iter)
                f(iter->link);
            return f;
        }

        template<typename... ARGS> 
        bool link(ArcList<LINK, not IN>& other, ARGS&&... args) {
            if(linked_to(other)) return false;
            auto linker = new Linker(*this, other, std::forward<ARGS>(args)...);
            join(linker);
            other.join(linker);
        }
        void unlink(ArcList<LINK, not IN>& other) {
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
            //std::lock_guard<std::mutex> lock(arclist_mutex);
            return bool(trail_search(iterator(first_link), [other](iterator iter) {
                //std::lock_guard<std::mutex> lock(iter->ptr_mutex);
                return iter.other() == &other; }));
        }
        size_t size() const {
            size_t count = 0;
            //std::lock_guard<std::mutex> lock(arclist_mutex);
            for_each([&count](const Linker<LINK>&) { ++count; });
            return count;
        }
    };


    template<typename LINK, bool IN>
    class ArcList<LINK, IN>::iterator {
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

