import java.util.*;


public class Buckets {
    private List<String> zeroBucket;
    private List<String> oneBucket;

    public Buckets(){
        zeroBucket = new ArrayList<>();
        oneBucket = new ArrayList<>();
    }

    public void addZero(String newValue){
        zeroBucket.add(newValue);
    }

    public void addOne(String newValue){
        oneBucket.add(newValue);
    }

    public List<String> getAllInOrder(){
        List<String> result = new ArrayList<>();

        for(String val: oneBucket){
            result.add(val);
        }

        for(String val: zeroBucket){
            result.add(val);
        }
        return result;
    }

    public void print(List<String> T){
        for(String num: T){
            System.out.print(num + " ");
        }
        System.out.println("");
    }

    public static void main(String[] args) {
        String[] origNumbers = {"0011", "1001","1000","0111","0101"};
        List<String> numbers = new ArrayList<>();
        for(String num: origNumbers){
            numbers.add(num);
        }
        int numDigits = 4;
        sort(numbers, numDigits);
    }

    public static List<String> sort(List<String> bin, int n){
        Buckets buckO = new Buckets();

        List<String> tmp = new ArrayList<>(bin);
        buckO.print(tmp);
        for(int i = 0; i < n; i++){
            Buckets buck = new Buckets();

            for(int j = 0; j < tmp.size(); j++){
                String val = tmp.get(j);
                char c = val.charAt((n-1)-i);


                if(c == '1'){
                    buck.addOne(val);
                }else if(c == '0'){
                    buck.addZero(val);
                }
                
            }

            buck.print(buck.getAllInOrder());
            tmp = new ArrayList<>(buck.getAllInOrder());
        }
        return null;
    }
        
}