public class test {
    public static void main(String[] args) {
        int[] listA = new int[]{5, 10, 30, 35};
        int[] listB = new int[listA.length];

        for (int i = 0; i < listA.length; i++) {
            listB[i] = listA[i];
        }

        System.out.println("listA: " + listA);
    }
}