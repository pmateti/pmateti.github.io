public static  void main(String[] args) {
    int []a = {12,23,43,34,3,6,7,1,9,6};
    {  
	int temp;
	for (int i = 0;i < a.length;i++) {  
	    for (int j = 0;j < a.length-i;j++ ) {
		if (a[j]>a[j+1]) {  
		    temp = a[j];
		    a[j+1] = a[j];
		    a[j+1] = temp;
		}
	    }
	}
    }
    for(int i = 0; i < a.length; i++) {
	System.out.print(a[i] + " ");
    }
}
