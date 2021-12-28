/*
 * THREAD POOLS
 * Demo extra: The fork/join pool
 *
 * ForkJoinPool is the central part of the fork/join framework introduced in Java 7.
 * It solves a common problem of spawning multiple tasks in recursive algorithms.
 * Using a simple ThreadPoolExecutor, you will run out of threads quickly,
 * as every task or subtask requires its own thread to run.
 *
 * In a fork/join framework, any task can spawn (fork) a number of subtasks and wait for their completion
 * using the join method. The benefit of the fork/join framework is that it does not create a new thread
 * for each task or subtask, implementing the Work Stealing algorithm instead.
 * https://www.baeldung.com/thread-pool-java-and-guava
 */

package demo11;

import java.util.Arrays;
import java.util.List;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.ForkJoinTask;
import java.util.concurrent.RecursiveTask;
import java.util.stream.Collectors;



public class AppExtra {

    public static void main(String[] args) {
        var tree =
                new TreeNode(5,
                        new TreeNode(-1),
                        new TreeNode(3,
                                new TreeNode(6),
                                new TreeNode(-4))
        );

        var forkJoinPool = ForkJoinPool.commonPool();

        int result = forkJoinPool.invoke(new TreeSumTask(tree));

        System.out.println(result);
    }

}



class TreeNode {
    int value;
    List<TreeNode> children;

    TreeNode(int value, TreeNode... children) {
        this.value = value;
        this.children = Arrays.asList(children);
    }
}



class TreeSumTask extends RecursiveTask<Integer> {
    private static final long serialVersionUID = 1L;

    final TreeNode node;

    TreeSumTask(TreeNode node) {
        this.node = node;
    }

    @Override
    protected Integer compute() {
        return node.value
                + node.children.stream()
                .map(child -> new TreeSumTask(child).fork())
                .collect(Collectors.summingInt(ForkJoinTask::join));
    }
}
