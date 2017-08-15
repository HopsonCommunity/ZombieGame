# Overview

This document shows how you can get started with contributing to this community project.

If you want to merge your code into the project, you should join our Discord server.
We continuously discuss ideas and things to do -- so just come up, ask
for help, and they will give you a task.

You should check out some Git Tutorials, as you will need to know about
cloning, commiting, branching, conflict resolving and basic git commands.

# Getting started

First, install Git on your computer. You can use the GitHub App installer, but
we wont use the GitHub App for our git stuff. The GitHub App Installer installs
some command line tools we need to use. Don't be alarmed about the complexity of these!
Once you get the hang of it, things will make sense. Pinky promise!

As a second step: Fork the project. The development team has
decided to use forks to keep everything clean. You can fork the project by
clicking the fork button on the upper right side of the github page.

After that, clone the fork. Open the Git Shell and navigate to the folder you want
the project to be in. Copy the clone URL from the address bar of the fork,
or look it up on the GitHub UI.

Next, enter this in the shell:

`git clone <fork-URL>`

Git should now download the fork. When finished downloading, change the the current
directory to the repository's root:

`cd Community-Game`

There is only a slight problem now: How can we update our fork if someone makes
a change to the main repository?
The first step to this is to add another remote to our local repository.

Enter this in the shell:

`git remote add upstream https://github.com/Hopson97/Community-Game`

Now the original repository where we forked from is now being added as another
remote. That means we can pull all the changes from that remote into our own
local repository to keep it up-to-date with the main development repository.

# Working on a feature
If you are working on a feature, create a separate branch for it. This way all your work will be separated from the everyone else's work and you'll keep your repository clean, avoiding unnecessary conflicts.

For example: you're implementing an inventory system.

1.  First, you need to create a branch for it and work there.
    ```
    $ git branch inventory
    $ git checkout inventory
    ```
    or do both in one step.
    ```
    $ git checkout -b inventory
    ```

2.  You create some files and commit them.
    ```
    $ git add .
    $ git commit -m "Implemented an inventory system"
    ```

3.  Meanwhile, other guys fixed a crucial bug with world generator and merged it into master. It's always good to keep your branch up to date when making a pull request, so you need to get these changes.

    The best way of doing that is to update the `master` branch, which is only for the code on the upstream and then [`rebase`](https://git-scm.com/docs/git-rebase) changes from master into the `inventory` branch.

    On branch `inventory`:
    ```
    $ git checkout master # change the branch to master
    $ git pull upstream master # pull the changes
    $ git checkout inventory # go to inventory branch
    $ git rebase master # move all the new commits from the master branch before your current work
    ```

    Or, if you don't need new changes in your master right now and don't want to type so much, then you can pull changes with the rebase instead of merge.

    On branch `inventory`:
    ```
    $ git pull upstream master -r # -r stands for rebase
    ```

4.  Then you need to push your changes to your fork and then make a pull request.
    ```
    $ git push origin inventory
    ```

# The pull request

And now you just make a pull request from `origin/inventory` to `upstream/master`.
When your PR is merged you can safely delete the `inventory` branch, or, if you
want to continue working on the inventory system, just pull the merge as describedin point 3.

HAVE FUN CODING
