import os
import threading


def run_task(items, target, args, cpu_count=os.cpu_count()):
    """
    Splits items in several batches and runs target function with args on each batch in parallel
    (on same number of threads as cpu cores)

    :param items: list of items to be processed in parallel
    :param target: worker function (first parameter must be a list of items to be processed)
    :param args: the parameters that the worker function is called with
    :param cpu_count: number of cores to be used
    """
    chunk = len(items) // cpu_count
    threads = []
    for startIndex in range(0, cpu_count):
        if startIndex == cpu_count - 1:
            filesToProcess = items[startIndex * chunk:]
        else:
            filesToProcess = items[startIndex * chunk: (startIndex + 1) * chunk]
        thread = threading.Thread(target=target, args=[filesToProcess] + args)
        threads.append(thread)
        thread.start()
    for t in threads:
        t.join()
