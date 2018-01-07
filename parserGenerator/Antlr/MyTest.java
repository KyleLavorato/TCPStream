public class MyTest {
     private static int magic_counter=777;

     public static void mymain() {   // <=== We will call this 
         System.out.println("Hello, World in java from mymain");
         System.out.println(magic_counter);
     }
     public static int mymain2(int n) {   // <== add this new function
        for (int i=0; i<n; i++)  {    
            System.out.print (i);
            System.out.println("Hello, World !");
        }
        return n*2;                    // return twice the param
    }
    public static void main (String[] args) {    // test in java
          //… some code here. 
    }
    private int uid;       // private data of the object: it's ID
    public MyTest() {      // constructor
        uid = magic_counter++ * 2;
    }
    public void showId() {  // simple method that shows the id of the object
        System.out.println(uid);
    }
    public native void doTest();  // to be supplied in C++ trhough JNI

     public void showId() {  // replace the previous version of example 5
         System.out.println(uid);
         doTest();         // <==== invoke the native method
     }
}

// g++ -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux TEST.cpp -o TEST -L/usr/lib/jvm/java-8-oracle/jre/lib/amd64/server/ -ljvm
