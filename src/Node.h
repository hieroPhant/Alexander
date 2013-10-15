#ifndef AlexanderNode_h
#define AlexanderNode_h

#include <memory>
#include <mutex>

namespace alex {
    template<typename LINK>
    class Node {
        class Linker {
            Node* source, target;
            std::mutex ptr_mutex;
            std::shared_ptr<Linker> next_input, next_output;
            LINK link;
            bool ready; //need this? make it atomic?
        };

        std::unique_ptr<Linker> input_head, output_head;
        std::mutex node_mutex;

        void clean(Linker& linker) {
            auto seek = [](std::shared_ptr<Linker>& linker_ptr) {
            };
        }

    public:
        Node() = default;
        Node(const Node& rhs) = delete;
        Node(Node&& rhs);
        Node& operator=(const Node& rhs) = delete;
        Node& operator=(Node&& rhs);
        ~Node();

        template<typename FUNCTION> FUNCTION for_inputs(FUNCTION f) const;
        template<typename FUNCTION> FUNCTION for_outputs(FUNCTION f) const;

        bool link(Node& source, LINK& new_link);
        bool link(Node& source, LINK&& new_link);
        template<typename... ARGS> bool emplace_link(ARGS... args);
        bool mirror(const Node& other);
        void unlink(Node& source);
        void unlink_all();
        bool linked_to(const Node& source) const;
        size_t size() const;
    };

    template<typename LINK> Node<LINK>::Node(Node&& rhs) {}
    template<typename LINK> Node& Node<LINK>::operator=(Node&& rhs) {}
    template<typename LINK> Node::~Node() {
        unlink_all();
    }
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
    template<typename LINK> bool Node<LINK>::link(Node& source, LINK& new_link) {}
    template<typename LINK> bool Node<LINK>::link(Node& source, LINK&& new_link) {}
    template<typename LINK> template<typename... ARGS> bool Node<LINK>::emplace_link(ARGS... args) {}
    template<typename LINK> bool Node<LINK>::mirror(const Node& other) {}
    template<typename LINK> void Node<LINK>::unlink(Node& source) {}
    template<typename LINK> void Node<LINK>::unlink_all() {}
    template<typename LINK> bool Node<LINK>::linked_to(const Node& other) const {}
    template<typename LINK> size_t Node<LINK>::size() const {}

} 

#endif

