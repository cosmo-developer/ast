#include "map.h"
#include EXP_H
#include <stdlib.h>
_node new_ast(){
	_node node=CAST_NODE(malloc(sizeof(node_)));
	node->type=DEFAULT;
	return node;
}

_bon new_bin_op(_node left,short _operator,_node right){
	_bon node=CAST_BIN(malloc(sizeof(bon_)));
	node->type=BIN;
	node->left=left;
	node->_operator=_operator;
	node->right=right;
	return node;
}

_nn new_num(short type,int ival,float fval,double dval,short sval,char cval){
	_nn node=CAST_NUM(malloc(sizeof(nn_)));
	_value val=CAST_VALUE(malloc(sizeof(value_)));
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

_va make_assign(const char* varname,_node expr){
	_va node=CAST_VAR(malloc(sizeof(va_)));
	node->expr=expr;
	node->type=VA;
	node->varname=varname;
}

_un make_unary(_node expr){
	_un node=CAST_UNR(malloc(sizeof(un_)));
	node->expr=expr;
	node->type=UNARY;
}

void clean_visit(_node node){
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

_value visit_bin(_bon);
_value visit_unary(_un);
_value visit_num(_nn);

_value visit(_node node){
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
_value visit_bin(_bon node){
	_value lvalue=visit(node->left);
	_value rvalue=visit(node->right);
	_value result=CAST_VALUE(malloc(sizeof(value_)));
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
_value visit_unary(_un node){
	_value result=CAST_VALUE(malloc(sizeof(value_)));
	_value previous=visit(CAST_NODE(node));
	result->type=DOUBLE;
	result->value.dval=-previous->value.dval;
	return result;
}
_value visit_num(_nn node){
	return copy_val(node->value);
}
_node copy(_node node){
	switch(node->type){
		case DEFAULT:{
			_node newnode=CAST_NODE(malloc(sizeof(node_)));
			newnode->type=node->type;
			return newnode;
		}
		case BIN:{
			_bon newnode=CAST_BIN(malloc(sizeof(bon_)));
			newnode->left=copy(CAST_BIN(node)->left);
			newnode->right=copy(CAST_BIN(node)->right);
			newnode->type=node->type;
			newnode->_operator=CAST_BIN(node)->_operator;
			return CAST_NODE(newnode);
		}
		case NUM:{
			_nn newnode=CAST_NUM(malloc(sizeof(nn_)));
			newnode->type=node->type;
			newnode->value=copy_val(CAST_NUM(node)->value);
			return CAST_NODE(newnode);
		}
		case UNARY:{
			_un newnode=CAST_UNR(malloc(sizeof(un_)));
			newnode->type=node->type;
			newnode->expr=copy(CAST_UNR(node)->expr);
			return CAST_NODE(newnode);
		}
	}
}
_value copy_val(_value val){
	_value newvalue=CAST_VALUE(malloc(sizeof(value_)));
	switch(val->type){
		case DOUBLE:
			newvalue->type=DOUBLE;
			newvalue->value.dval=val->value.dval;
			return newvalue;
	}
}
