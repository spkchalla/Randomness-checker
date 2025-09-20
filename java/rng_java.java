import java.io.*;
import java.util.*;

public class rng_java {
    public static void main(String[] args){
        if(args.length<3){
            System.err.println("Usage: java rng_java <seed> <output_file> <mode: chi|ks>");
            System.exit(1);
        }

        int seed = Integer.parseInt(args[0]);
        String filename = args[1];
        String mode = args[2];

        try (PrintWriter out = new PrintWriter(new FileWriter(filename))){
            Random rand = new Random(seed);
            out.println("#seed = "+ seed);

            if(mode.equals("chi")){
                // I should be generating 5000 numbers for this
                for(int i = 0; i< 5000; i++){
                    int num = rand.nextInt(1000) +1;
                    out.println(num);
                }
            }else if(mode.equals("ks")){
                for(int i = 0; i< 30; i++){
                    double num = rand.nextDouble() * 5.0;
                    out.printf("%.6f%n", num);
                }
            }else{
                System.err.println("Invalid mode. Use chi or ks.");
                System.exit(1);
            }
        }catch(IOException e){
            System.err.println("Cannot open file" + filename);
            System.exit(1);
        }
    }
}