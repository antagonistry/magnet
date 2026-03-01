# magnet - Minimalistic build system
magnet is an interpreted minimal build language made by @antagonistry and is
blazingly fast and extremely light-weighted, it also only have 8 keywords
to remember!

## Keywords
__'#':__    does nothing
__'!':__    create task that check for error and stop the script if found error
__'@':__    create task that check for error
__'$':__    create task that check for error without stopping the script
__'%':__    create task that doesn't check for any error
__'^':__    create task that only run if there is any error inside the previous task
__'/':__    create task that only run if there isn't any error inside the previous task
__':':__    run command that will return error if found
__'-':__    run command that won't return any error

## Safety
magnet is considered to be unsafe build language, cause it can cause fork bomb
by the shell, but magnet can also be considered as a safe language when only
looking at the interpreter.

## Examples
Here's an example build script that would output "Hello, World!".

```sh
!
    :echo "Hello, World!"
```

Yeah, is it that easy? just two line of code and we're done!
Also here's another example for opening a firefox tab.

```sh
!firefox
    :example.com
```

If you want to add a little bit of flavor and use the conditional
keyword like `/` and `^`, see this!

```sh
$not_a_command
    :arg

    /
        -echo "Execution successful."
    ^
        -echo "Execution failed."
```

You may now see this like an object-oriented language but don't worry,
in reality, it's just a 1 dimensional language, meaning that the language
itself has no depth, look at this script after it's been parsed.

```sh
$not_a_command
:arg

/
-echo "Execution successful."
^
-echo "Execution failed."
```

Let's come to the fun part, becareful, this is a fork bomb!

```sh
# This script's named fork.mg

!magnet
    -fork.mg
```

What this code does is that it spawns version of itself again and again until
there's an error and it'll eventually force quit itself, unlike the fork bomb
in shell.

## End
