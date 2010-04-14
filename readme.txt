Some basic restructuring of the second semester C project.
I hope this one is final - 6 rewrites are WAAAY too much, but that's the price on not being able to properly decide on the architecture.

But now it has some nifty features:
  - SSE intrinsics math library (some things, like matrix multiplication is kinda crude, but works), needs mroe functions, like some fast sin/cos, some easing functions etc.
  - C++'s template-like (templates in C, yay!) generic linked table container + hashtable of pointers (needs some re-instantiation guard still)

I also dropped the whole mech idea for now, since it would need animations and possibly other too bothersome stuff and instead opted for a standard space shooter/half-simulator with models ripped from Homeworld 2. For now I plan to recreate the second mission (convoy defense) with some additional cool stuff (like giving Angel Moon asteroid ring or sth).
I plan to somehow follow the HW2 asset format, be it scripts, model or anything else (which may require LUA and stuff), to cut down on my own effort put into assets (and possibly get some good, tested ideas off the code) and concentrate on coding.