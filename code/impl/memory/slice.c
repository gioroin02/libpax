#ifndef PAX_CORE_MEMORY_SLICE_C
#define PAX_CORE_MEMORY_SLICE_C

#include "slice.h"

Pax_Slice
pax_slice_make(void* memory, paxiword start, paxiword stop, paxiword stride)
{
    return pax_slice_make_amount(memory, start, stop - start, stride);
}

Pax_Slice
pax_slice_make_amount(void* memory, paxiword index, paxiword amount, paxiword stride)
{
    Pax_Slice result = {0};

    if (memory != 0 && index >= 0 && amount > 0 && stride > 0) {
        paxiword diff = index * stride;

        result.memory = pax_as(paxu8*, memory) + diff;
        result.length = amount;
        result.stride = stride;
    }

    return result;
}

void*
pax_slice_zero(Pax_Slice self)
{
    for (paxiword i = 0; i < self.length * self.stride; i += 1)
        self.memory[i] = 0;

    return self.memory;
}

void*
pax_slice_flip(Pax_Slice self)
{
    paxiword index = 0;
    paxiword other = self.stride * (self.length - 1);

    while (index < other) {
        for (paxiword i = 0; i < self.stride; i += 1) {
            paxu8 left  = self.memory[index + i];
            paxu8 right = self.memory[other + i];

            self.memory[index + i] = right;
            self.memory[other + i] = left;
        }

        index += self.stride;
        other -= self.stride;
    }

    return self.memory;
}

void*
pax_slice_copy(Pax_Slice self, Pax_Slice value)
{
    if (self.length != value.length || self.stride != value.stride)
        return 0;

    for (paxiword i = 0; i < self.length * self.stride; i += 1)
        self.memory[i] = value.memory[i];

    return self.memory;
}

void*
pax_slice_copy_flipped(Pax_Slice self, Pax_Slice value)
{
    if (self.length != value.length || self.stride != value.stride)
        return 0;

    paxiword index = 0;
    paxiword other = self.stride * (self.length - 1);

    while (index < other) {
        for (paxiword i = 0; i < self.stride; i += 1)
            self.memory[index + i] = value.memory[other + i];

        index += self.stride;
        other -= self.stride;
    }

    return self.memory;
}

void*
pax_slice_shift(Pax_Slice self, paxiword index, paxiword amount, paxiword offset)
{
    paxuword value = pax_mag_integer(offset);

    switch (pax_sgn_integer(offset)) {
        case +1:
            return pax_slice_shift_forw(self, index, amount, value);

        case -1:
            return pax_slice_shift_back(self, index, amount, value);

        default: break;
    }

    return self.memory;
}

void*
pax_slice_shift_forw(Pax_Slice self, paxiword index, paxiword amount, paxiword offset)
{
    index  = pax_between(index,  0, self.length);
    amount = pax_between(amount, 0, self.length - index);

    paxiword start = self.stride * index;
    paxiword stop  = self.stride * index + self.stride * amount;
    paxiword diff  = self.stride * offset;

    offset = pax_between(offset, 0, self.length - start);
    offset = pax_between(offset, 0, self.length - stop);

    for (paxiword i = stop; i > start; i -= 1) {
        paxu8 value = self.memory[i - 1];

        self.memory[i + diff - 1] = value;
        self.memory[i - 1]        = 0;
    }

    return self.memory;
}

void*
pax_slice_shift_back(Pax_Slice self, paxiword index, paxiword amount, paxiword offset)
{
    index  = pax_between(index,  0, self.length);
    amount = pax_between(amount, 0, self.length - index);

    paxiword start = self.stride * index;
    paxiword stop  = self.stride * index + self.stride * amount;
    paxiword diff  = self.stride * offset;

    offset = pax_between(offset, 0, self.length - start);
    offset = pax_between(offset, 0, self.length - stop);

    for (paxiword i = start; i < stop; i += 1) {
        paxu8 value = self.memory[i];

        self.memory[i - diff] = value;
        self.memory[i]        = 0;
    }

    return self.memory;
}

paxb8
pax_slice_is_equal(Pax_Slice self, Pax_Slice value)
{
    if (self.length != value.length || self.stride != value.stride)
        return 0;

    for (paxiword i = 0; i < self.length * self.stride; i += 1) {
        if (self.memory[i] != value.memory[i])
            return 0;
    }

    return 1;
}

paxiword
pax_slice_elements(Pax_Slice self)
{
    return self.length;
}

paxb8
pax_slice_peek_pure(Pax_Slice self, paxiword index, void* memory, paxiword stride)
{
    if (index < 0 || index >= self.length)
        return 0;

    if (stride != self.stride) return 0;

    paxiword temp = self.stride * index;

    if (memory != 0) {
        for (paxiword i = 0; i < self.stride; i += 1)
            pax_as(paxu8*, memory)[i] = self.memory[temp + i];
    }

    return 1;
}

void*
pax_slice_peek_pure_or_null(Pax_Slice self, paxiword index)
{
    if (index < 0 || index >= self.length)
        return 0;

    return &self.memory[index * self.stride];
}

paxb8
pax_slice_update_pure(Pax_Slice self, paxiword index, void* memory, paxiword stride)
{
    if (index < 0 || index >= self.length || stride != self.stride)
        return 0;

    paxiword temp = self.stride * index;

    if (memory != 0) {
        for (paxiword i = 0; i < self.stride; i += 1)
            self.memory[temp + i] = pax_as(paxu8*, memory)[i];

        return 1;
    }

    for (paxiword i = 0; i < self.stride; i += 1)
        self.memory[temp + i] = 0;

    return 1;
}

paxb8
pax_slice_write(Pax_Slice self, paxiword index, Pax_Slice value)
{
    if (self.stride != value.stride) return 0;

    if (index < 0 || index + value.length > self.length)
        return 0;

    Pax_Slice slice = pax_slice_make_amount(
        self.memory, index, value.length, self.stride);

    pax_slice_copy(slice, value);

    return 1;
}

paxb8
pax_slice_read(Pax_Slice self, paxiword index, Pax_Slice value)
{
    if (self.stride != value.stride) return 0;

    if (index < 0 || index + value.length > self.length)
        return 0;

    Pax_Slice slice = pax_slice_make_amount(
        self.memory, index, value.length, self.stride);

    pax_slice_copy(value, slice);

    return 1;
}

#endif // PAX_CORE_MEMORY_SLICE_C
