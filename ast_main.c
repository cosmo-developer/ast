#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include EXP_H

int main(int argc, char **argv) {
	//evaluating (6+5)/11
	struct ast_node* lnum=CAST_NODE(new_num(DOUBLE,0,0,5,0,0));
	struct ast_node* rnum=CAST_NODE(new_num(DOUBLE,0,0,6,0,0));
	struct ast_node* bin=CAST_NODE(new_bin_op(lnum,ADD,rnum));
	struct ast_node* div=CAST_NODE(new_bin_op(bin,DIV,CAST_NODE(new_num(DOUBLE,0,0,11,0,0))));
	struct ast_value* result=visit(div);
	printf("%lf\n",result->value.dval);
	free(result);
	CLEAN(bin);
	return 0;
}
