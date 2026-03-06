#pragma once

struct subvector_c {
    int *mas;
    unsigned int top;
    unsigned int capacity;
};

bool init(subvector_c *qv);
bool push_back(subvector_c *qv, int d);
int pop_back(subvector_c *qv);
bool resize(subvector_c *qv, unsigned int new_capacity);
void shrink_to_fit(subvector_c *qv);
void clear(subvector_c *qv);
void destructor(subvector_c *qv);
void print_subvector(subvector_c *qv);