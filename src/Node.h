#ifndef AlexanderNode_h
#define AlexanderNode_h

#include <memory>
#include <mutex>

namespace alex {

    template<typename LINK, bool IN> List;

    template<typename LINK>
    struct Linker {
        //inherit from Head?
        List<LINK, true>* target;
        List<LINK, false>* source;
        std::mutex ptr_mutex;
        Linker* next_input, next_output;
        LINK link;

        template<typename... ARGS> 
        Linker(List<LINK,false>& from, List<LINK,true>& to, ARGS... args) 
            : target(&to), source(&from), next_input(nullptr), next_output(nullptr), link(args...) {}

        template<typename... ARGS>
        Linker(List<LINK,true>& to, List<LINK,false>& from, ARGS... args) 
            : Linker(from, to, args...) {}
    };


    template<typename LINK, bool IN>
    class List {
        class iterator;

        std::mutex head_mutex;
        Linker<LINK>* first_link;
        void join(Linker<LINK>* new_linker) {
            iterator iter(new_linker);
            iter.me() = this;
            iter.next() = first_link;
            first_link = new_linker;
        }
        void break_next(iterator iter) {
            auto trail = iter++;
            trail.next() = iter.next();
            clean(iter);
        }
        void clean(iterator iter) {
            iter.me() = nullptr;
            if(iter.other() == nullptr) delete &(*iter);
            else {
                //search other list and remove
            }
        }
        template<typename FUNCTION>
        iterator search(iterator iter, FUNCTION f) {
            if(!bool(iter) || f(iter)) return iter;
            else return search(++iter, f);
        }
        template<typename FUNCTION>
        iterator trail_search(iterator iter, FUNCTION f) {
            auto trail = iter++;
            if(!bool(iter) || f(iter)) return trail;
            else return trail_search(iter, f);
        }
        template<typename FUNCTION>
        FUNCTION for_each_linker(FUNCTION f) {
            for(iterator iter(first_link); bool(iter); ++iter)
                f(*iter);
            return f;
        }
        
    public:
        List() : first_link(nullptr) {}
        List& List(const List& rhs);
        List& operator=(const List& rhs);
        ~List() { unlink_all(); }

        template<typename FUNCTION> for_each(FUNCTION f) const {
            for_each_linker([&f](Linker<LINK>& linker) { f(linker.link); });
            return f;
        }

        template<typename... ARGS> 
        bool link(List<LINK, not IN>& other, ARGS... args) {
            if(linked_to(other)) return false;
            auto linker = new Linker(*this, other, args...);
            join(linker);
            other.join(linker);
        }
        bool clone(const List& model); //use copy constructor for this?
        void unlink(List<LINK, not IN>& other) {
            iterator iter(first_link);
            if(iter.other() == &other) {
                first_link = iter.next();
                clean(iter);
                return;
            }
            for(auto trail=iter++; bool(iter); trail=iter++) {
                if(iter.other() == &other) {
                    break_next(trail);
                    return;
                }
            }
        }
        void unlink_all();

        bool linked_to(const List<LINK, not IN>& other) const {
            return bool(search(iterator(first_link), [other](iterator iter) {
                return iter.other() == &other; }));
        }
        size_t size() const {
            size_t count = 0;
            for_each([&count](const Linker<LINK>&) { ++count; });
            return count;
        }
    };


    template<typename LINK, bool IN>
    class List<LINK, IN>::iterator {
        Linker<LINK>* current;

        Linker<LINK>*& next_impl(std::true_type) { return current->next_input; }
        Linker<LINK>*& next_impl(std::false_type) { return current->next_output; }

        List<LINK, not IN>* list_ref(std::true_type) { return current->source; }
        List<LINK, not IN>* list_ref(std::false_type) { return current->target; }

    public:
        iterator() : current(nullptr) {}
        explicit iterator(Linker<LINK>* linker_ptr) : current(linker_ptr) {}

        explicit operator bool() const { return current; }
        iterator& operator++() { current = next(); return *this; }
        iterator operator++(int) { auto temp = *this; current = next(); return temp; }

        Linker<LINK>& operator*() { return *current; }
        Linker<LINK>* operator->() { return current; }

        bool operator==(const iterator& other) const { return current == other.current; }
        bool operator!=(const iterator& other) const { return !(*this == other); }

        Linker<LINK>*& next() { return next_impl(IN); }
        List<LINK, not IN>* other() { return list_ref(IN); }
        List<LINK, not IN>*& me() { return list_ref(not IN); }
    };


    template<typename LINK>
    class Node {
        //unique_ptrs would require deletion of copy and assignment
        struct Links { Head<true> inputs; Head<false> outputs; };
        std::shared_ptr<Links> links;

    public:
        template<typename FUNCTION>
        FUNCTION Node::for_inputs(FUNCTION f) const;
        template<typename FUNCTION>
        FUNCTION Node::for_outputs(FUNCTION f) const;

        template<typename... ARGS> bool link(Node& source, ARGS... args);
        bool mirror(const Node& other);
        void unlink_all();
        
        bool linked_to(const Node& other) const;
        size_t size() const;
    };

    template<typename LINK> template<typename FUNCTION> 
    FUNCTION Node<LINK>::for_inputs(FUNCTION f) const {
        
        auto traverse = [f](Linker& linker) {
            f(linker.link);
            if(!linker.next_input) return f;
            return traverse(*linker.next_input);
        };
        return traverse(*input_head, f);
    }
    template<typename LINK> template<typename FUNCTION> 
    FUNCTION Node<LINK>::for_outputs(FUNCTION f) const {
        auto traverse = [f](Linker& linker) {
            f(linker.link);
            if(!linker.next_output) return f;
            return traverse(*linker.next_output);
        };
        return traverse(*output_head, f);
    }
    template<typename LINK> 
    template<typename... ARGS> 
    bool Node<LINK>::emplace_link(Node& source, ARGS... args) {}
    template<typename LINK> bool Node<LINK>::mirror(const Node& other) {}
    template<typename LINK> void Node<LINK>::unlink(Node& source) {}
    template<typename LINK> void Node<LINK>::unlink_all() {}
    template<typename LINK> bool Node<LINK>::linked_to(const Node& other) const {}
    template<typename LINK> size_t Node<LINK>::size() const {}

} 

#endif

