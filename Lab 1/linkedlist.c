l_ptr add_ordered(l_ptr list, int value) {
	//create new node
	l_ptr newest = (l_ptr) malloc(sizeof(l_rec));
	l_ptr front = list;
	l_ptr previous = NULL;
	newest->next = NULL;
	newest->val = value;
	//if list is empty, add node
	if(list == NULL) return newest;
	//if new value is less than first node in list, add to front
	else if(value < list->val){
		newest->next = list;
		front = newest;
	}
	//iteratively search list until placement is found
	else{
		while((list->next != NULL) && value>((list->next)->val)){
			//previous = list;
			list = list->next;
		}
		//if at end of list, add to back
		if(list->next == NULL) list->next = newest;
		//put new node between two nodes
		else{
			newest->next = list->next;
			list->next = newest;
			
		}
	} 
	return front;
}

