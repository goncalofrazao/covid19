#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "restrict_data.h"
#include "structures.h"

void remove_struct(fix_t *to_remove, fix_t **head)
{
    if (to_remove->previous != NULL)
    {
        to_remove->previous->next = to_remove->next;
    }
    else
    {
        (*head) = to_remove->next;
    }
    to_remove->next->previous = to_remove->previous;
    free(to_remove);
}