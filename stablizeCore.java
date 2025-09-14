import java.util.LinkedList;
import java.util.Queue;

public class stablizeCore {

    public static void solution(int input) {
        Queue<Integer> queue = new LinkedList<>();
        int[] cnt = new int[input + 1];
        int[] parent = new int[input + 1];

        queue.add(input);
        parent[input] = 0;

        while (!queue.isEmpty()) {
            int value = queue.poll();

            if (value == 0 ) break; // 탈출 조건

            if (value % 3 == 0 && cnt[value / 3] == 0) {
                queue.add(value / 3);
                cnt[value / 3] = cnt[value] + 1;
                parent[value / 3] = value;
            }
            if (value % 2 == 0 && cnt[value / 2] == 0) {
                queue.add(value / 2);
                cnt[value / 2] = cnt[value] + 1;
                parent[value / 2] = value;
            }
            if (value > 1 && cnt[value - 1] == 0) {
                queue.add(value - 1);
                cnt[value - 1] = cnt[value] + 1;
                parent[value - 1] = value;
            }
        }
        System.out.printf("%d\n", cnt[1]);
        int[] answer = new int[cnt[1]+1];
        int count = cnt[1]+1;
        for (int i = 1; i != 0; i = parent[i]) { // 1에서부터 부모로 거슬러 올라감
            count--;
            answer[count] = i;
        }
        for (int i = 0; i < answer.length; i++) {
            System.out.printf("%d ", answer[i]);
        }

    }

    public static void main(String[] args) {
        int input = 10;
        solution(input);
    }
}
