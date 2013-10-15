template<typename LINK>
class Node {
    class Linker {
        Node* source, target;
        Linker* next;
        LINK link;
    };

    Linker* input_head, output_head;
};

