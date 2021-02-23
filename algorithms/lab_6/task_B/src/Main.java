import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    static int n = 1000001;

    static class Node{
        String key;
        String data;

        public Node(String key, String data){
            this.key = key;
            this.data = data;
        }
    }

    public static int hash(String x){
        int h = 0;
        int g = 1;
        String key = x.toLowerCase();
        for (int i = 0; i<key.length();i++)
        {
            char ch = key.charAt(i);
            h += (int)(ch - 'a') * g % n;
            h %= n;
            g *= 53;
            g %= n;
        }
        return h;
    }

    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(new File("map.in"));
        FileWriter writer = new FileWriter("map.out");
        ArrayList<Node>[] array = new ArrayList[n];
        while (scanner.hasNext()) {
            String cmd = scanner.next();
            String x = scanner.next();
            if(cmd.equals("put")){
                int h = hash(x);
                String data = scanner.next();
                if(array[h]==null){
                    array[h] = new ArrayList<>();
                    array[h].add(new Node(x,data));
                }else {
                    boolean f = true;
                    for(int i = 0; i < array[h].size();i++){
                        Node rc = array[h].get(i);
                        if(rc.key.equals(x)){
                            rc.data = data;
                            f = false;
                            break;
                        }
                    }
                    if(f){
                        array[h].add(new Node(x,data));
                    }
                }
            }
            if(cmd.equals("get")){
                int h = hash(x);
                if(array[h]!=null) {
                    String data = null;
                    for(int i = 0; i < array[h].size();i++){
                        Node rc = array[h].get(i);
                        if(rc.key.equals(x)){
                            data = rc.data;
                            break;
                        }
                    }
                    if (data!=null) {
                        writer.write(data+"\n");
                    } else {
                        writer.write("none\n");
                    }
                }else writer.write("none\n");
            }
            if(cmd.equals("delete")){
                int h = hash(x);
                if(array[h]!=null) {
                    Node rc1 = null;
                    for(int i = 0; i < array[h].size();i++){
                        Node rc = array[h].get(i);
                        if(rc.key.equals(x)){
                            rc1 = rc;
                            break;
                        }
                    }
                    if (rc1 != null) {
                        array[h].remove(rc1);
                    }
                }
            }
        }
        writer.close();
    }

}