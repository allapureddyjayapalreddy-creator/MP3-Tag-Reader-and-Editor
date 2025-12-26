#ifndef TYPES_H
#define TYPES_H

/* Status will be used in fn. return type */
typedef enum
{
    e_failure,
    e_success,
    v_failure,
    v_success
} Status;


typedef enum
{
    e_view,
    e_edit,
    e_unsupported
} OperationType;

#endif
