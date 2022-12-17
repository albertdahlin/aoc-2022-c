#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "String.h"


#define appendTo(sizes, size) \
    assert(sizes##_idx < 1024); \
    sizes[sizes##_idx] = size; \
    sizes##_idx++

#define parseInt(var) \
    var = 0; \
    if (!Char_isDigit(*cur)) goto error; \
    while (Char_isDigit(*cur) && cur < end) { \
        var = var * 10 + *cur - '0'; \
        cur++; \
    }


#define skipUntil(exp) \
    while (!(exp) && cur < end) cur++

#define skipLine() \
    skipUntil(*cur == '\n')

typedef struct {
    size_t dircount;
    size_t dirsize;
} Context;


typedef struct {
    Context stack[64];
    size_t idx;
} Context_Stack;


static Context Context_push(Context_Stack *stack, Context ctx)
{
    assert(stack->idx < 64);
    stack->stack[stack->idx] = ctx;
    stack->idx++;

    return (Context){0};
}

static Context Context_pop(Context_Stack *stack)
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
    Context  ctx = {0};
    Context_Stack stack = {0};

    char *cur = input.data;
    char *end = input.data + input.length;

    // skip first "cd /"
    skipLine();

    for (; cur < end; cur++) {
        if (*cur == '$') {
            // Command
            // skip to next letter, commands start with letter.
            skipUntil(*cur >= 'a');
            if (*cur == 'c') {
                // "cd" starts with 'c'
                skipLine();

                if (cur[-1] == '.') {
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
                    // "cd dir"
                    ctx = Context_push(&stack, ctx);
                }

            } else if (*cur == 'l') {
                // ls
                skipLine();
            }
        } else if (*cur == 'd') {
            // dir
            skipLine();
            ctx.dircount += 1;
        } else if (Char_isDigit(*cur)) {
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

    snprintf(buffer.data, buffer.length, "%14lu %14lu", part1, part2);
    return;

    error:
    printf("Parse error at %lu, %.10s\n", cur - input.data, cur);
}

