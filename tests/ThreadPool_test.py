import os
import sys

sys.path.append(os.path.join(os.getcwd(), "src"))

import time
import unittest
from concurrent.futures import Future
from multiprocessing import cpu_count

from classes.WorkerPool import WorkerPool


def test_func(x):
    time.sleep(1)
    return x * x


class TestWorkerPool(unittest.TestCase):
    # Test Initialization of WorkerPool
    def test_initialization(self):
        # Default initialization
        pool_default = WorkerPool()
        self.assertEqual(pool_default.workers, cpu_count())
        self.assertEqual(pool_default.pool_type, "thread")

        # Custom initialization
        custom_workers = 5
        custom_pool_type = "process"
        pool_custom = WorkerPool(workers=custom_workers, pool_type=custom_pool_type)
        self.assertEqual(pool_custom.workers, custom_workers)
        self.assertEqual(pool_custom.pool_type, custom_pool_type)

    # Test Adding Workers
    def test_adding_workers(self):
        initial_workers = 3
        pool = WorkerPool(workers=initial_workers)
        pool.add_worker(2)
        self.assertEqual(pool.workers, initial_workers + 2)

    # Test Removing Workers
    def test_removing_workers(self):
        initial_workers = 5
        pool = WorkerPool(workers=initial_workers)
        pool.remove_worker(2)
        self.assertEqual(pool.workers, initial_workers - 2)

    # Test Append Future
    def test_append_future(self):
        pool = WorkerPool()
        future = Future()
        pool.append_future(future)
        self.assertIn(future, pool.futures)

    # Test Appending Multiple Futures
    def test_appending_multiple_futures(self):
        pool = WorkerPool()
        futures = [Future() for _ in range(3)]
        pool.append_futures(*futures)
        for future in futures:
            self.assertIn(future, pool.futures)

    # Test Function Execution
    def test_function_execution(self):
        pool = WorkerPool()
        pool.append(test_func, 2)
        result = pool.execute()
        self.assertEqual(result, [4])

    # Test Map Function
    def test_map_function(self):
        pool = WorkerPool()
        results = pool.map(test_func, range(3))
        self.assertEqual(results, [0, 1, 4])

    # Test Execution of Futures
    def test_execution_of_futures(self):
        pool = WorkerPool()
        for i in range(3):
            pool.append(test_func, i)
        results = pool.execute()
        self.assertEqual(results, [0, 1, 4])

    # Test Pool Closure
    def test_pool_closure(self):
        pool = WorkerPool()
        pool.close()
        self.assertTrue(not pool.is_alive)

    # Test Context Manager Support
    def test_context_manager(self):
        with WorkerPool() as pool:
            pool.append(test_func, 2)
        self.assertTrue(not pool.is_alive)


unittest.main()
