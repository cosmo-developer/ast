#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H
#define EXPRESSION_SOURCE_PATH "includes/expressions.h"
#define AUTHOR "Sonu Aryan"
#define EMAIL "cosmoorganization@gmail.com"
#define MAP_DATA EXP_H

#define CAST_NODE(node) ((struct ast_node*)node)
#define CAST_BIN(node)  ((struct bin_op_node*)node)
#define CAST_NUM(node)  ((struct num_node*)node)
#define CAST_VAR(node)  ((struct var_assign*)node)
#define CAST_UNR(node)  ((struct unary_node*)node)
#define CAST_VALUE(node) ((struct ast_value*)node)

#define CLEAN(node) clean_visit(node)

#ifndef VALUE_TYPE
#define VALUE_TYPE
#define INT 0
#define FLOAT 1
#define DOUBLE 2
#define SHORT 3
#define CHAR 4
#define CCSTR 5
#define CSTR 6
#endif

#ifndef NODE_TYPE
#define NODE_TYPE
#define DEFAULT 0
#define BIN 1
#define NUM 2
#define UNARY 3
#define VA1 4
#define VA 5
#endif

#ifndef MATH_OP
#define MATH_OP
#define ADD 1
#define MINUS 2
#define DIV 3
#define MOD 4
#define MUL 5
#define AND 6
#define OR 7
#define GT 8
#define LT 9
#define GTE 10
#define LTE 11
#define EQ 12
#define NE 13
#endif

#ifndef VALUE
#define VALUE
struct ast_value{short type;union{char cval;short sval;int ival;float fval;double dval;char* cstr;const char* ccstr;} value;};
#endif

#ifndef NODES
#define NODES
struct ast_node{short type;};
struct bin_op_node{short type; struct ast_node* left; short _operator; struct ast_node* right;};
struct num_node{short type; struct ast_value* value;};
struct unary_node{short type;struct ast_node* expr;};
struct var_assign_1{short type;struct ast_node* lhand;struct ast_node* rhand;};
struct var_assign{short type;const char* varname;struct ast_node* expr;};
#endif

#ifndef NODE_SHORT
#define NODE_SHORT
typedef struct ast_node* _node;
typedef struct bin_op_node* _bon;
typedef struct num_node* _nn;
typedef struct unary_node* _un;
typedef struct var_assign_1* va1;
typedef struct var_assign* _va;
typedef struct ast_value* _value;

typedef struct ast_node node_;
typedef struct bin_op_node bon_;
typedef struct num_node nn_;
typedef struct unary_node un_;
typedef struct var_assign_1 va1_;
typedef struct var_assign va_;
typedef struct ast_value value_;
#endif

#ifndef MAKERS
#define MAKERS
_node new_ast();
_bon new_bin_op(_node left,short _operator,_node right);
_nn new_num(short type,int ival,float fval,double dval,short sval,char cval);
_un make_unary(_node expr);
_va make_assign(const char* varname,_node expr);

void clean_visit(_node node);
_node copy(_node);
_value copy_val(_value);
#endif

#ifndef EVALUATORS
#define EVALUATORS
_value visit(_node);
#endif

#endif
