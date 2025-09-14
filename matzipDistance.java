import java.util.*;

public class matzipDistance {
    static int N, M;
    static int[][] house;
    static int[][] matzip;
    static int houseCount, matzipCount;

    public static int solution(String input) {
        int result = Integer.MAX_VALUE;
    
        // 데이터 전처리
        String[] inputLines = input.split("\n");

        String[] nm = inputLines[0].split(" ");
        N = Integer.parseInt(nm[0]);
        M = Integer.parseInt(nm[1]);

        int[][] inputArray = new int[N][N];

        for (int i = 1; i <= N; i++) {
            String[] strArr = inputLines[i].split(" ");
            for (int j = 0; j < N; j++) {
                inputArray[i-1][j] = Integer.parseInt(strArr[j]);
            }
        }

        matzip = new int[13][2]; // 맛집 정보 - X, Y의 형태로 저장
        matzipCount = 0;
        house = new int[2 * N][2]; // 주택 정보 - X, Y의 형태로 저장
        houseCount = 0;

        // 주거지 및 맛집 위치 파악
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (inputArray[i][j] == 1) {
                    house[houseCount][0] = i;
                    house[houseCount][1] = j;    
                    houseCount++;            
                } else if (inputArray[i][j] == 2) {
                    matzip[matzipCount][0] = i;
                    matzip[matzipCount][1] = j;
                    matzipCount++;                
                }
            }
        }

        // 조합 생성 및 최소 거리 계산
        result = comb(new ArrayList<>(), 0, 0, Integer.MAX_VALUE);

        return result;
    }

    private static int comb(List<Integer> selected, int start, int depth, int minResult) {
        if (depth == M) {
            int sum = calcDistance(selected);
            return Math.min(minResult, sum);
        }

        for (int i = start; i < matzipCount; i++) {
            selected.add(i);
            minResult = comb(selected, i + 1, depth + 1, minResult);
            selected.remove(selected.size() - 1);
        }

        return minResult;
    }

    // 거리 계산
    private static int calcDistance(List<Integer> selected) {
        int sum = 0;
        for (int h = 0; h < houseCount; h++) {
            int hx = house[h][0];
            int hy = house[h][1];
            int dist = Integer.MAX_VALUE;

            for (int idx : selected) {
                int mx = matzip[idx][0];
                int my = matzip[idx][1];
                dist = Math.min(dist, Math.abs(hx - mx) + Math.abs(hy - my));
            }

            sum += dist;
        }
        return sum;
    }

    public static void main(String[] args) {
        String input = "5 2\n" +
                        "0 2 0 1 0\n" +
                        "1 0 1 0 0\n" +
                        "0 0 0 0 0\n" +
                        "0 0 0 1 1\n" +
                        "0 0 0 1 2\n";

        int result = solution(input);

        System.out.println(result);
    }
}
