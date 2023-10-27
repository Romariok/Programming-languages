from subprocess import *

test_inputs = ["soda1", "soda2", "soda3", "book", "", "rbetrbebre", "1111111", "wrfgbewthnwrsthnwrnrghnrnjrgnawlkbqhrejgaqneqarvjqqqqqqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjqjq"]
expected_outputs = ["Root beer", "Fanta", "Coke", "", "", "", "", ""]
expected_errors = ["", "", "", "Not found", "Not found", "Not found", "Not found", "Failed to read word"]


def build() -> None:
    process: CompletedProcess = run(["make", "main"], stdout=DEVNULL, stderr=DEVNULL)
    try:
        process.check_returncode()
        print("Compiled successfully.")
    except CalledProcessError:
        print(f"Compilation finished with code {process.returncode}.")
        exit()



def test():
   fail_num = 0
   build()
   for i in range(len(test_inputs)):
      process = Popen(["./main"], stdin=PIPE, stdout=PIPE, stderr=PIPE)
      stdout, stderr = process.communicate(input=test_inputs[i].encode())
      stdout = stdout.decode().strip()
      stderr = stderr.decode().strip()

      if stdout == expected_outputs[i] and stderr == expected_errors[i]:
         print("Test %s passed" % i)
      else:
         fail_num += 1
         print("Test %s failed" % i)
         print("Input: %s" % test_inputs[i])
         print("Awaited output: %s" % expected_outputs[i])
         print("Stdout: %s" % stdout.strip())
         print("Awaited error: %s" % expected_errors[i])
         print("Stderr: %s" % stderr.strip())
         print("Exit code: %s" % process.returncode)
      print("-------------------")

   if fail_num == 0:
      print("All tests passed")
   else:
      print("%d tests failed" % fail_nums)

test()