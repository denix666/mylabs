#!/usr/bin/env python

import curses
myscreen = curses.initscr()
myscreen.border(0)
myscreen.addstr(10, 50, "See Curses, See Curses Run!")
myscreen.refresh()
myscreen.getch()
curses.endwin()
