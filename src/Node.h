#ifndef AlexanderNode_h
#define AlexanderNode_h

#include <memory>
#include <mutex>

namespace alex {
    template<typename LINK>
    class Node {
        class Linker {
            //inherit from Head?
            Head* source, target;
            std::mutex ptr_mutex;
            Linker* next_input, next_output;
            LINK link;
            bool ready; 
        };

        class Head {
            std::mutex head_mutex;
            Linker* first_link;
            void clean(Head& other);

        public:
            Head();
            Head& Head(const Head& rhs);
            Head& operator=(const Head& rhs);
            ~Head();

            template<typename FUNCTION> FUNCTION for_each(FUNCTION f) const;
        };

        //unique_ptrs would require deletion of copy and assignment
        struct Links { Head inputs, outputs; };
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
        bool size() const;
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

