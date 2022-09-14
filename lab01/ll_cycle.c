#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head)
{
    /* your code here */
    node *tortoise = head;
    node *hare = head;
    if (head != 0)
    {
        do
        {
            if ((hare = hare->next) == 0)
                return 0;
            else if ((hare = hare->next) == 0)
                return 0;
            else
                ;
            tortoise = tortoise->next;
        } while (tortoise != hare);

        return 1;
    }
    else
        return 0;
}