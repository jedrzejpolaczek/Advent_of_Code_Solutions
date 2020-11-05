#include <iostream> //std::cout
#include <memory> //std::shared_ptr

struct node {
    int val;
    std::shared_ptr<struct node> next;
};

int main(int argc, char const* argv[])
{
    const int step = 377;
    std::shared_ptr<struct node> head = std::make_shared<struct node>();
    std::shared_ptr<struct node> curr = head;
    head->val = 0;
    head->next = head;

    for (int i = 1; i <= 2017; i++) {

        for (int j = 0; j < step; j++)
            curr = curr->next;

        std::shared_ptr<struct node> temp = curr->next;
        std::shared_ptr<struct node> new_node = std::make_shared<struct node>();
        new_node->val = i;
        curr->next = new_node;
        new_node->next = temp;
        curr = new_node;
    }

    std::cout << curr->next->val << std::endl;

    int answer_pt2 = 0;

    for (int i = 1, idx = 0; i <= 50000000; i++) {
        idx = (idx + 1 + step) % i;
        if (idx == 0) answer_pt2 = i;
    }

    std::cout << answer_pt2 << std::endl;

    return 0;
}