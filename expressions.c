#include "map.h"
#include EXP_H
#include <stdlib.h>
struct ast_node* new_ast(){
	struct ast_node* node=(struct ast_node*)malloc(sizeof(struct ast_node));
	node->type=DEFAULT;
	return node;
}

struct bin_op_node* new_bin_op(struct ast_node* left,short _operator,struct ast_node* right){
	struct bin_op_node* node=(struct bin_op_node*)malloc(sizeof(struct bin_op_node));
	node->type=BIN;
	node->left=left;
	node->_operator=_operator;
	node->right=right;
	return node;
}

struct num_node* new_num(short type,int ival,float fval,double dval,short sval,char cval){
	struct num_node* node=(struct num_node*)malloc(sizeof(struct num_node));
	struct ast_value* val=(struct ast_value*)malloc(sizeof(struct ast_value));
	switch(type){
		case FLOAT:
			node->type=NUM;
			val->type=type;
			val->value.fval=fval;
			node->value=val;
			break;
		case INT:
			node->type=NUM;
			val->type=type;
			val->value.ival=ival;
			node->value=val;
			break;
		case DOUBLE:
			node->type=NUM;
			val->type=type;
			val->value.dval=dval;
			node->value=val;
			break;
	}
	return node;
}

struct var_assign* make_assign(const char* varname,struct ast_node* expr){
	struct var_assign* node=(struct var_assign*)malloc(sizeof(struct var_assign));
	node->expr=expr;
	node->type=VA;
	node->varname=varname;
}

struct unary_node* make_unary(struct ast_node* expr){
	struct unary_node* node=(struct unary_node*)malloc(sizeof(struct unary_node));
	node->expr=expr;
	node->type=UNARY;
}

void clean_visit(struct ast_node* node){
	switch(node->type){
		case 0:
			free(node);
			break;
		case BIN:
			clean_visit(((struct bin_op_node*)node)->left);
			clean_visit(((struct bin_op_node*)node)->right);
			free(node);
			break;
		case NUM:
			free(((struct num_node*)node)->value);
			free(node);
			break;
		case VA:
			clean_visit(((struct var_assign*)node)->expr);
			free(node);
			break;
		case UNARY:
			clean_visit(((struct unary_node*)node)->expr);
			free(node);
			break;
	}
}

