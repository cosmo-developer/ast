#include "map.h"
#include EXP_H
#include <stdlib.h>
struct ast_node* new_ast(){
	struct ast_node* node=CAST_NODE(malloc(sizeof(struct ast_node)));
	node->type=DEFAULT;
	return node;
}

struct bin_op_node* new_bin_op(struct ast_node* left,short _operator,struct ast_node* right){
	struct bin_op_node* node=CAST_BIN(malloc(sizeof(struct bin_op_node)));
	node->type=BIN;
	node->left=left;
	node->_operator=_operator;
	node->right=right;
	return node;
}

struct num_node* new_num(short type,int ival,float fval,double dval,short sval,char cval){
	struct num_node* node=CAST_NUM(malloc(sizeof(struct num_node)));
	struct ast_value* val=CAST_VALUE(malloc(sizeof(struct ast_value)));
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
	struct var_assign* node=CAST_VAR(malloc(sizeof(struct var_assign)));
	node->expr=expr;
	node->type=VA;
	node->varname=varname;
}

struct unary_node* make_unary(struct ast_node* expr){
	struct unary_node* node=CAST_UNR(malloc(sizeof(struct unary_node)));
	node->expr=expr;
	node->type=UNARY;
}

void clean_visit(struct ast_node* node){
	switch(node->type){
		case 0:
			free(node);
			break;
		case BIN:
			clean_visit(CAST_BIN(node)->left);
			clean_visit(CAST_BIN(node)->right);
			free(node);
			break;
		case NUM:
			free(CAST_NUM(node)->value);
			free(node);
			break;
		case VA:
			clean_visit(CAST_VAR(node)->expr);
			free(node);
			break;
		case UNARY:
			clean_visit(CAST_UNR(node)->expr);
			free(node);
			break;
	}
}

//visit models

struct ast_value* visit_bin(struct bin_op_node*);
struct ast_value* visit_unary(struct unary_node*);
struct ast_value* visit_num(struct num_node*);

struct ast_value* visit(struct ast_node* node){
	if (node ==  NULL)exit(-1);
	switch(node->type){
		case BIN:
			return visit_bin(CAST_BIN(node));
		case UNARY:
			return visit_unary(CAST_UNR(node));
		case NUM:
			return visit_num(CAST_NUM(node));
	}
}
struct ast_value* visit_bin(struct bin_op_node* node){
	struct ast_value* lvalue=visit(node->left);
	struct ast_value* rvalue=visit(node->right);
	struct ast_value* result=CAST_VALUE(malloc(sizeof(struct ast_value)));
	switch(node->_operator){
		case ADD:
			result->type=DOUBLE;
			result->value.dval=lvalue->value.dval+rvalue->value.dval;
			break;
		case MINUS:
			result->type=DOUBLE;
			result->value.dval=lvalue->value.dval-rvalue->value.dval;
			break;
		case DIV:
			result->type=DOUBLE;
			result->value.dval=lvalue->value.dval/rvalue->value.dval;
			break;
		case MUL:
			result->type=DOUBLE;
			result->value.dval=lvalue->value.dval*rvalue->value.dval;
			break;
	}
	return result;
}
struct ast_value* visit_unary(struct unary_node* node){
	struct ast_value* result=CAST_VALUE(malloc(sizeof(struct ast_value)));
	struct ast_value* previous=visit(CAST_NODE(node));
	result->type=DOUBLE;
	result->value.dval=-previous->value.dval;
	return result;
}
struct ast_value* visit_num(struct num_node* node){
	return copy_val(node->value);
}
struct ast_node* copy(struct ast_node* node){
	switch(node->type){
		case DEFAULT:{
			struct ast_node* newnode=CAST_NODE(malloc(sizeof(struct ast_node)));
			newnode->type=node->type;
			return newnode;
		}
		case BIN:{
			struct bin_op_node* newnode=CAST_BIN(malloc(sizeof(struct bin_op_node)));
			newnode->left=copy(CAST_BIN(node)->left);
			newnode->right=copy(CAST_BIN(node)->right);
			newnode->type=node->type;
			newnode->_operator=CAST_BIN(node)->_operator;
			return CAST_NODE(newnode);
		}
		case NUM:{
			struct num_node* newnode=CAST_NUM(malloc(sizeof(struct num_node)));
			newnode->type=node->type;
			newnode->value=copy_val(CAST_NUM(node)->value);
			return CAST_NODE(newnode);
		}
		case UNARY:{
			struct unary_node* newnode=CAST_UNR(malloc(sizeof(struct unary_node)));
			newnode->type=node->type;
			newnode->expr=copy(CAST_UNR(node)->expr);
			return CAST_NODE(newnode);
		}
	}
}
struct ast_value* copy_val(struct ast_value* val){
	struct ast_value* newvalue=CAST_VALUE(malloc(sizeof(struct ast_value)));
	switch(val->type){
		case DOUBLE:
			newvalue->type=DOUBLE;
			newvalue->value.dval=val->value.dval;
			return newvalue;
	}
}
