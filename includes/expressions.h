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

#ifndef MAKERS
#define MAKERS
struct ast_node* new_ast();
struct bin_op_node* new_bin_op(struct ast_node* left,short _operator,struct ast_node* right);
struct num_node* new_num(short type,int ival,float fval,double dval,short sval,char cval);
struct unary_node* make_unary(struct ast_node* expr);
struct var_assign* make_assign(const char* varname,struct ast_node* expr);

void clean_visit(struct ast_node* node);
struct ast_node* copy(struct ast_node*);
struct ast_value* copy_val(struct ast_value*);
#endif

#ifndef EVALUATORS
#define EVALUATORS
struct ast_value* visit(struct ast_node*);
#endif

#endif
