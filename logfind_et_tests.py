import subprocess
import os

import unittest
"""
./logfind  fileName  string
"""


class LogfindTest(unittest.TestCase):

    def setUp(self):
        self.cmd = ["./logfind"]
        self.fileTogrep = ["temporaryFile.txt"]

    def test_grep_for_single_word(self):
        self.assertEqual(b"11	drwxrwxr-x  2 duszek duszek  4096 lip 25 23:01 __pycache__/\n",
                         subprocess.run(self.cmd + self.fileTogrep + ["__pycache__"], stdout=subprocess.PIPE).stdout)


if __name__ == '__main__':
    unittest.main(warnings='ignore')

