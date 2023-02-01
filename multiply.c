#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>



void grade_school_algo(int a[], int b[]);
void partial_product_sum(int pass[], int ans[]);
void print_answer(int a[]);
void karatsuba_multi(int a[], int b[], int answerlist[], int len_of_a, int len_of_b);
void sum_two_list(int a[1024], int b[1024], int len_a, int len_b, int returnlist[1024], int len_return[]);
void minus_two_list(int a[2048], int b[2048], int returnlist[2048]);
void sum_two_list2048(int a[2048], int b[2048], int returnlist[2048]);


int cnt = 0; // for print(cnt =1000 then print)

int main() {
	int first_number[1024] = { -1 };
	int second_number[1024] = { -1 };
	// declare two variable(lists) for inputs.

	
	int forinit_number = -1;
	// just for int list initialization

	char first_nuberforstr[1026] = "";
	char second_nuberforstr[1026] = "";
	// declare two variable(string lists) for inputs. this will be saving one by one to int list. 
	// +2 size for "\n" is made by fgets-> will be remove
	
	int i = 0;
	for (i = 0; i < 1024; i++) first_number[i] = forinit_number;
	for (i = 0; i < 1024; i++) second_number[i] = forinit_number;
	// initialization two lists - all -1




	while (1) {


		if (!fgets(first_nuberforstr, sizeof(first_nuberforstr), stdin)){
			printf("fail to fgets \n");
			return 0;

		}
		// first input fgets

		if (!strchr(first_nuberforstr, '\n')) {
			printf("fail to over 1024 digit \n");
			return 0;
		}
		// if digit > 1024 then program will quit

		if (first_nuberforstr[0] == '\n') {
			printf("there is no input \n");
			return 0;
		}
		// if no input then will quit

		if (!fgets(second_nuberforstr, sizeof(second_nuberforstr), stdin)) {
			printf("fail to fgets \n");
			return 0;

		}
		// second input fgets

		if (!strchr(second_nuberforstr, '\n')) {
			printf("fail to over 1024 digit \n");
			return 0;
		}
		// if digit > 1024 then program will quit

		if (second_nuberforstr[0] == '\n') {
			printf("there is no input \n");
			return 0;
		}
		// if no input then will quit


		first_nuberforstr[strlen(first_nuberforstr) - 1] = '\0';
		second_nuberforstr[strlen(second_nuberforstr) - 1] = '\0';
		// remove last \n -> because of fgets


		

		int j = 0;
		for (j = 0; j < strlen(first_nuberforstr); j++) {
			first_number[j] = first_nuberforstr[strlen(first_nuberforstr) - j-1]-48;
		}
		for (j = 0; j < strlen(second_nuberforstr); j++) {
			second_number[j] = second_nuberforstr[strlen(second_nuberforstr) - j - 1] - 48;
		}
		// parse char to int using -48, and inverse order and save in first_number, second number list.


		int first_number2[1024];
		int second_number2[1024];
		memcpy(first_number2, first_number, 1024 * sizeof(int));
		memcpy(second_number2, second_number, 1024 * sizeof(int));
		// copy the list


		struct timeval start_t;

		struct timeval end_t;
		double checktime;
		gettimeofday(&start_t, NULL);

		for(int k = 0; k < 1000; k++)
			grade_school_algo(first_number, second_number);

		gettimeofday(&end_t, NULL);
		checktime = (end_t.tv_sec - start_t.tv_sec )*1000000.0f + (end_t.tv_usec - start_t.tv_usec);
		printf(" Grade-school: %.3f us", checktime/1000.0f);
		

		//grade school algorithm excute #1000 and check how much time using gettimeof day.



		int answerlist2[2048];
		for (i = 0; i < 2048; i++)
			answerlist2[i] = -1;
			
		

		int len_of_a = 0;
		int len_of_b = 0;
		for (i = 0; i < 1024; i++) {
			if (first_number2[i] < 0 ) {
				len_of_a = i;
				break;
			}
		}
		if (first_number2[1023] > 0)
			len_of_a = 1024;
		for (i = 0; i < 1024; i++) {
			if (second_number2[i] < 0 ) {
				len_of_b = i;
				break;
			}
		}
		if (second_number2[1023] > 0)
			len_of_b = 1024;
		// (input a & b)'s length calculate



		struct timeval start_t2;
		struct timeval end_t2;
		gettimeofday(&start_t2, NULL);
		for (int k = 0; k < 1000; k++) {
			
			karatsuba_multi(first_number2, second_number2, answerlist2, len_of_a, len_of_b);

		}

		gettimeofday(&end_t2, NULL);
		checktime = (end_t2.tv_sec - start_t2.tv_sec)*1000000.0f +  (end_t2.tv_usec - start_t2.tv_usec);
		

		printf("\n");
		print_answer(answerlist2);
		printf(" Karatsuba: %.3f us", checktime/1000.0f);

		printf("\n");


		cnt = 0; //reset cnt




		memset(first_nuberforstr, '\0', sizeof(first_nuberforstr));
		memset(second_nuberforstr, '\0', sizeof(second_nuberforstr));
		memset(answerlist2, '\0', sizeof(answerlist2));
		for (i = 0; i < 1024; i++) first_number[i] = forinit_number;
		for (i = 0; i < 1024; i++) second_number[i] = forinit_number;
		// reset(refresh) all list

	}


	return 0;
}




void grade_school_algo(int a[], int b[]) {

	int number_of_pass = 0; // if 4+9 then number_of_pass is 1, if 8*8, then number_of_pass is 6. like that
	int saving_number = 0;// for saving temporary number
	int passlist[1025]; // for saving partial product ex) 12*34 ->first passlist[0] is 8, passlist[1] is 4 -> next will be reset and change passlist[0] = 6, ..[1] = 3
	
	int i = 0;
	int j = 0; // just use for loop

	cnt++; // if cnt = 1000 then print answer.

	for (i = 0; i < 1025; i++) {
		passlist[i] = -1;
	}
	// initialization list to all -1


	int answerlist[2048]; // answer is inverse order of answer

	for (int i = 0; i < 2048; i++) {
		answerlist[i] = -1;
	}
	// initialization list to all -1
	
	for (i = 0; i < 1024; i++) {
		for (j = 0; j < 1024; j++) {

			if (a[j] >= 0 && b[i] >= 0) {
				saving_number = ((a[j] * b[i]) + number_of_pass) % 10; // 7+9 -> 6 save in saving_number and 1 carry save in number_of_pass
				number_of_pass = (a[j] * b[i] + number_of_pass) / 10;
				passlist[j] = saving_number; 
			}
			else
				break;
		}
		if (number_of_pass > 0) {
			passlist[j] = number_of_pass;
			number_of_pass = 0;
		}
		if (passlist[0] < 0)
			break;
		// ex) 12*34 ->first passlist[0] is 8, passlist[1] is 4 -> next will be reset and change passlist[0] = 6, ..[1] = 3


		// sum passlist to answerlist. answerlist push one space by pointer
		partial_product_sum(passlist, answerlist+i); // this is the key 



		for (int i2 = 0; i2 < 1025; i2++) {
			passlist[i2] = -1;
		}
		// initialization list to all -1
	}

	for (int i2 = 0; i2 < 1025; i2++) {
		passlist[i2] = -1;
	}
	// initialization list to all -1 just double check. sry



	for (int kk = 0; kk < 2048; kk++)
	{
	
		if (answerlist[kk] < 0)
			break;
	}



	if (cnt >= 1000)
		print_answer(answerlist); // print anwerlist -> [1,3,4,-1,-1...] -> print 431

	for (int i = 0; i < 2048; i++) {
		answerlist[i] = -1;
	}
	// initialization list to all -1



}


/*
12*34 =>
   48
+ 36
= 408

first passlist -> {8,4,-1,...}
anslist add first passlist

secon passlist -> {6,3,-1,-1,...}
anslist+1(sizeof int) add second passlist

then
anslist = { 8,0,4,-1,-1,...}

*/

// this fuction using for grade_argolithm. 
// sum passlist to answerlist. add each one space.
void partial_product_sum(int pass[], int ans[]) {
	
	int pass_number = 0; // if 4+9 then number_of_pass is 1, if 8*8, then number_of_pass is 6. like that
	int i = 0;
	int savetemp = 0;

	for (int i = 0; i < 1024; i++) {

		if (ans[i] < 0)
			ans[i] = 0;
		if (ans[i+1] < 0)
			ans[i+1] = 0;
		// change minus 1 to zero

		if (pass[i] >= 0) {
			int temp1 = (ans[i] + pass[i] + pass_number); // carry(pass_number) -> 1 or 0

			ans[i] = (ans[i] + pass[i]+pass_number) % 10;
			pass_number = temp1 / 10;
			
		}	
		else if (pass[i] < 0) {

			savetemp = i;
			break;
		}


	}


	if (pass[savetemp] < 0 && pass_number != 0) 
	{

		if (ans[savetemp] < 0)
			ans[savetemp] = 0;
		if (ans[savetemp +1] < 0)
			ans[savetemp +1] = 0;

		int temp =  ans[savetemp] + pass_number;

		ans[savetemp] =( ans[savetemp] + pass_number )  % 10;
		ans[savetemp + 1] = ans[savetemp + 1] + temp / 10;

	}

}



// if input {7,4,2,4,0,-1,-128581282,....} -> print 4247
void print_answer(int a[]) {

	int i = 0;
	int len_of_answer = 0;

	for (i = 0; i < 2048; i++) {

		
		if (a[i] < 0 )
			break;

		len_of_answer++;

	}
	for (int j = 0; j < 2048; j++) {
		if (a[len_of_answer] <= 0 )
			len_of_answer--;
	}// for remove "0" or minus like 000123 -> remove 000


	for (i = len_of_answer; i >= 0; i--) {
		printf("%d", a[i]);

	}

	if (len_of_answer < 0)
		printf("0");

	printf(" ");

}




void karatsuba_multi(int a[], int b[], int answerlist[], int len_of_a, int len_of_b) {


	int halflen_a = 0; // half of len_of_a
	int halflen_b = 0; // half of len_of_b
	int divide_by_n = 0; // this is n
	int half_n = 0;  // this is n/2

	



	int i = 0; // just use loop





	if (len_of_a == 1 && len_of_b == 1) {


		answerlist[0] = (a[0] * b[0]) % 10;
		if (a[0] * b[0] >= 10)
			answerlist[1] = (a[0] * b[0]) / 10;

		return;

	} // if 1digit -> then return their multifly. 
	//ex) {5,-1,-1,...}, {6,-1,-1,...} => {0,3,-1,-1,-1,...}


	if (len_of_a == 0 || len_of_b == 0) {
		answerlist[0] = -1;
		answerlist[1] = -1;
		return;
	}
	// if 0,0 input then return {all minus list}




	// base case is 8 digit.
	// if under 8 digit -> list will be change int value and just use cc = aa * bb;
	if (len_of_a <= 8 && len_of_b <= 8) {
		long long int aa = (long long int) 0;
		long long int bb = (long long int) 0;

		long long int for10 = (long long int)1;

		for (int ii = 0; ii < len_of_a; ii++) {
			aa = aa + a[ii] * for10;
			for10 = for10 * (long long int)10;

		}
		for10 = 1;
		for (int ii = 0; ii < len_of_b; ii++) {
			bb = bb + b[ii] * for10;
			for10 = for10 * (long long int) 10;
		}
		// change int list -> long long int value


		long long int cc = 0;
		cc = aa * bb;
		// just multiply


		int kkk = 0;
		while (cc > 0) {
			answerlist[kkk] = (int)(cc % (long long int)10);
			cc = (cc / (long long int)10);
			kkk++;
		}
		// just input to answerlist

		return;
	}




	if (len_of_a % 2 == 0)
		halflen_a = len_of_a / 2;
	else
		halflen_a = (len_of_a - 1) / 2;

	if (len_of_b % 2 == 0)
		halflen_b = len_of_b / 2;
	else
		halflen_b = (len_of_b - 1) / 2;

	if (len_of_a >= len_of_b) {
		divide_by_n = len_of_b;
		half_n = halflen_b;
	}
	else {
		divide_by_n = len_of_a;
		half_n = halflen_a;
	}

	if (len_of_a == 1 || len_of_b == 1) {
		divide_by_n = 1;
		half_n = 1;
	}
	// calculate a/2, b/2, n, n/2
	// if odd a(or b) then halflen_a = (a-1)/2
	// n is min(a,b), if a is lower then n/2 is same to a/2



	/*

	int small_alist[1024];
	int small_blist[1024];
	int small_clist[1024];
	int small_dlist[1024];

	*/

	int* small_alist = (int*)malloc(sizeof(int) * 1024);
	int* small_blist = (int*)malloc(sizeof(int) * 1024);
	int* small_clist = (int*)malloc(sizeof(int) * 1024);
	int* small_dlist = (int*)malloc(sizeof(int) * 1024);

	int ac_list[2048];
	int bd_list[2048];

	
	for (i = 0; i < 1024; i++) {
		small_alist[i] = -1;

		small_blist[i] = -1;

		small_clist[i] = -1;

		small_dlist[i] = -1;
		ac_list[i] = -1;
		bd_list[i] = -1;
	}
	for(i = 1024; i<2048; i++){
		ac_list[i] = -1;
		bd_list[i] = -1;
	}
	



	memcpy(small_blist, a, half_n * sizeof(int));
	memcpy(small_alist, a + half_n, (len_of_a - half_n) * sizeof(int));
	memcpy(small_dlist, b, half_n * sizeof(int));
	memcpy(small_clist, b + half_n, (len_of_b - half_n) * sizeof(int));
	// ex) a= 123456 b = 1234 -> smalla = 1234, smallb = 56, smallc = 12, smalld = 34


	



	karatsuba_multi(small_alist, small_clist, ac_list, (len_of_a - half_n), (len_of_b - half_n));
	// multiply(a,c) -> return list is saved in ac_list



	karatsuba_multi(small_blist, small_dlist, bd_list, half_n, half_n);
	// multiply(b,d)-> return list is saved in bd_list


	/*
	int empty_list1[1024];
	int empty_list2[1024];
	int temp_2048list5[2048];
	*/

	int* aplusb_list1 = (int*)malloc(sizeof(int) * 1024);
	int* cplusd_list2 = (int*)malloc(sizeof(int) * 1024);
	int* temp_2048list5 = (int*)malloc(sizeof(int) * 2048);

	
	for (i = 0; i < 1024; i++) {
		aplusb_list1[i] = -1;

		cplusd_list2[i] = -1;
		temp_2048list5[i] = -1;
	}
	for(i = 1024; i<2048; i++)
		temp_2048list5[i] = -1;
	



	int len_a = 0;
	int len_b = 0;
	int len_a1[1] = { 0 };
	int len_b1[1] = { 0 };


	sum_two_list(small_alist, small_blist, (len_of_a - half_n), half_n, aplusb_list1, len_a1); // aplusb_list: a+b
	sum_two_list(small_clist, small_dlist, (len_of_b - half_n), half_n, cplusd_list2, len_b1); // cplusd_list: c+d


	free(small_alist);
	free(small_clist);
	free(small_blist);
	free(small_dlist);


	len_a = len_a1[0];
	len_b = len_b1[0];
	
	karatsuba_multi(aplusb_list1, cplusd_list2, temp_2048list5, len_a, len_b); // multiply(a+b, c+d) -> save templist

	free(aplusb_list1);
	free(cplusd_list2);


	/*
	int empty_2048list5[2048];
	int empty_2048list6[2048];
	int empty_2048list1[2048];
	int empty_2048list2[2048];
	int empty_2048list4[2048];
	*/

	int*  empty_2048list1 = (int*)malloc(sizeof(int) * 2048);
	int*  empty_2048list2 = (int*)malloc(sizeof(int) * 2048);
	int*  empty_2048list4 = (int*)malloc(sizeof(int) * 2048);
	int*  empty_2048list5 = (int*)malloc(sizeof(int) * 2048);
	int*  abcd_list = (int*)malloc(sizeof(int) * 2048);


	
	for (i = 0; i < 2048; i++) {
		empty_2048list5[i] = -1;

		abcd_list[i] = -1;
		empty_2048list1[i] = -1;
		empty_2048list2[i] = -1;
		empty_2048list4[i] = -1;
	}
	


	minus_two_list(temp_2048list5, ac_list, empty_2048list5); // empty_2048list5: temp - ac
	minus_two_list(empty_2048list5, bd_list, abcd_list); // abcd_list: temp - ac - bd



		

	for (i = 0; i < divide_by_n; i++)
		empty_2048list1[i] = 0;
	for (i = 0; i < half_n; i++)
		empty_2048list2[i] = 0;

	memcpy(empty_2048list1 + half_n*2, ac_list, 1024 * sizeof(int)); //empty_2048list1: ac*10^n
	memcpy(empty_2048list2+half_n, abcd_list,(2048-half_n)*sizeof(int)); // empty_2048list2: abcd*10^(n/2)



	sum_two_list2048(empty_2048list1, empty_2048list2,  empty_2048list4); // empty_2048list4: ac*10^n +  abcd*10^(n/2)


	sum_two_list2048(empty_2048list4, bd_list, answerlist);//  answerlist:  ac*10^n +  abcd*10^(n/2) + bd



	free(empty_2048list1);
	free(empty_2048list2);
	free(empty_2048list4);
	free(empty_2048list5);
	free(abcd_list);
	free(temp_2048list5);
}


// two list sum ex) {1,3,4,5,-1,-1,...} + {2,7,-1,-1,...} = {3,0,5,5,-1,-1,...} -> -1 is ignored
void sum_two_list(int a[1024], int b[1024], int len_a, int len_b, int returnlist[1024], int len_return[]) {

	int i = 0;
	int pass_number = 0;

	int untill_n = (len_a >= len_b) ? len_a : len_b;

	int temp_a = 0;
	int temp_b = 0;

	if (len_a == 0) {
		memcpy(returnlist, b, 1024 * sizeof(int));
		len_return[0] = len_b;
		return;
	}
	if (len_b == 0) {
		memcpy(returnlist, a, 1024 * sizeof(int));
		len_return[0] = len_a;
		return;
	}


	for (i = 0; i < untill_n; i++) {

		if (a[i] < 0 ) {
			temp_a = 0;
			temp_b = b[i];
		}
		else if (b[i] < 0 ) {
			temp_b = 0;
			temp_a = a[i];
		}
		else {
			temp_a = a[i];
			temp_b = b[i];

		}

		returnlist[i] = (temp_a + temp_b + pass_number) % 10;
		
		pass_number = (temp_a + temp_b + pass_number) / 10;

	}
	if (pass_number != 0)
		returnlist[i] = pass_number;

	if (returnlist[i] > 0)
		len_return[0] = i+1;
	else
		len_return[0] = i;


}


// two list sum ex) {1,3,4,5,-1,-1,...} + {2,7,-1,-1,...} = {3,0,5,5,-1,-1,...} -> -1 is ignored
void sum_two_list2048(int a[2048], int b[2048], int returnlist[2048]) {

	int i = 0;
	int pass_number = 0;

	int temp_a = 0;
	int temp_b = 0;

	for (i = 0; i < 2048; i++) {

		if ((a[i] < 0 && b[i] < 0))
			break;

		if (a[i] < 0 ) {
			temp_a = 0;
			temp_b = b[i];
		}
		else if (b[i] < 0 ) {
			temp_b = 0;
			temp_a = a[i];
		}
		else {
			temp_a = a[i];
			temp_b = b[i];
		}



		returnlist[i] = (temp_a + temp_b + pass_number) % 10;

		pass_number = (temp_a + temp_b + pass_number) / 10;

	}
	if (pass_number != 0 && i != 2048)
		returnlist[i] = pass_number;

	return;

}



// two list minus ex) {1,3,4,5,-1,-1,...} - {2,7,-1,-1,...} = {9,5,3,5,-1,-1,...} -> -1 is ignored
void minus_two_list(int a[2048], int b[2048], int returnlist[2048]) {

	int i = 0;

	int pass_number = 0;

	int temp_b = 0;


	for (i = 0; i < 2048; i++) {

		if (a[i] < 0 )
			break;
		else if (b[i] < 0 ) {
			temp_b = 0;

		}
		else
			temp_b = b[i];

		if (a[i] > temp_b)
			returnlist[i] = (a[i] - temp_b - pass_number);
		else if (a[i] ==  temp_b  && pass_number == 1)
			returnlist[i] = 9;
		else if (a[i] ==  temp_b  && pass_number == 0)
			returnlist[i] = 0;
		else 
			returnlist[i] = 10 + (a[i] - temp_b) - pass_number;

		pass_number = (a[i] - temp_b - pass_number) >= 0 ? 0 : 1;


	}


	for (int j = i; j >=0; j--) {
		if (returnlist[i] <= 0) {
			returnlist[i] = -1;
			i--;

		}
		else
			break;

	}

	return;

}
