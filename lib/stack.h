#ifndef _STACK_H_
#define _STACK_H_

#define STACK_INITIAL_SIZE	256

/* Do NOT manipulate the __stack structure directly unless you know what
 * you are doning. */
struct __stack
{
	char *base;
	unsigned int size;
	char *top;
};

typedef struct __stack stack_t;

#ifdef __cplusplus
extern "C"
{
#endif

stack_t *stack_create(unsigned int isize);
#define stack_push(elem, type, stack) \
({																			\
	(stack)->top + sizeof (type) <= (stack)->base + (stack)->size ||		\
		__stack_expand(stack, sizeof (type)) >= 0 ?							\
	*((type *)(stack)->top)++ = (elem), (stack)->top - (stack)->base : -1;	\
})
#define stack_pop(type, stack)	(*--(type *)(stack)->top)
#define stack_top(type, stack)	(*((type *)(stack)->top - 1))
#define stack_height(stack)		((stack)->top - (stack)->base)
#define stack_empty(stack)		((stack)->base == (stack)->top)
void stack_destroy(stack_t *stack);

/* Never call the following function directly. */
int __stack_expand(stack_t *stack, unsigned int esize);

#ifdef __cplusplus
}
#endif

#endif
