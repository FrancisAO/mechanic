from mechanic_command import MechanicCommand
from context import Mechanic
import sys

if __name__ == '__main__':
  exitCode = MechanicCommand(Mechanic(args=sys.argv[1:])).run()
  sys.exit(exitCode)
