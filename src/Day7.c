#include <inttypes.h>
#include <assert.h>
#include "String.h"

#define appendTo(sizes, size) assert(sizes##_idx < 1024); sizes[sizes##_idx] = size; sizes##_idx++
#define skipUntil(exp) while (!(exp) && current < end) current++
#define skipLine() skipUntil(*current == '\n')
#define parseInt(var) \
    var = 0; \
    if ('0' > *current || *current > '9') goto error; \
    while ('0' <= *current && *current <= '9' && current < end) { \
        var = var * 10 + *current - '0'; \
        current++; \
    }

typedef struct {
    size_t dircount;
    size_t dirsize;
} Context;


typedef struct {
    Context stack[64];
    size_t idx;
} Context_Stack;


Context Context_push(Context_Stack *stack, Context ctx)
{
    assert(stack->idx < 64);
    stack->stack[stack->idx] = ctx;
    stack->idx++;

    return (Context){0};
}

Context Context_pop(Context_Stack *stack)
{
    assert(stack->idx > 0);
    stack->idx--;

    return stack->stack[stack->idx];
}

void Day7_solve(String input, String buffer)
{
    uint64_t sizes[1024] = {0};
    size_t   sizes_idx = 0;
    uint64_t filesize = 0;
    Context ctx = {0};
    Context_Stack stack = {0};

    char *current = input.data;
    char *end = input.data + input.length;

    // skip first "cd /"
    skipLine();

    for (; current < end; current++) {
        if (*current == '$') {
            // Command
            // skip to next letter, commands start with letter.
            skipUntil(*current >= 'a');
            if (*current == 'c') {
                // cd
                skipLine();

                if (current[-1] == '.') {
                    // cd ..
                    filesize = ctx.dirsize;
                    if (ctx.dircount == 0) {
                        appendTo(sizes, ctx.dirsize);
                    }
                    ctx = Context_pop(&stack);
                    assert(ctx.dircount > 0);
                    ctx.dircount -= 1;
                    ctx.dirsize += filesize;
                } else {
                    // cd dir
                    ctx = Context_push(&stack, ctx);
                }

            } else if (*current == 'l') {
                // ls
                skipLine();
            }
        } else if (*current == 'd') {
            // dir
            skipLine();
            ctx.dircount += 1;
        } else if ('0' <= *current && *current <= '9') {
            // file
            parseInt(filesize);
            ctx.dirsize += filesize;
            skipLine();
        }
    }

    // Push the last size.
    if (ctx.dircount == 0) {
        appendTo(sizes, ctx.dirsize);
    }

    // Input does not end with "cd .." back to root.
    while (stack.idx > 0) {
        filesize = ctx.dirsize;
        ctx = Context_pop(&stack);
        assert(ctx.dircount > 0);
        ctx.dircount -= 1;
        ctx.dirsize += filesize;
        if (ctx.dircount == 0) {
            appendTo(sizes, ctx.dirsize);
        }
    }

    uint64_t part1 = 0;
    uint64_t part2 = 0;
    // Root will always be the last element.
    uint64_t usedSpace = sizes[sizes_idx - 1];
    uint64_t size;
    part2 = -1;

    for (size_t i = 0; i < sizes_idx; i++) {
        size = sizes[i];
        if (size <= 1e5) {
            part1 += size;
        }
        if ((7e7 - usedSpace + size) >= 3e7 && size < part2) {
            part2 = size;
        }
    }

    snprintf(buffer.data, buffer.length, "%10lu %10lu", part1, part2);
    return;

    error:
    printf("Parse error at %lu, %.10s\n", current - input.data, current);
}

