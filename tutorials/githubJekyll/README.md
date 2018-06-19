---
layout: default
title: Gitub Pages
---
<br>
## Step by step guide
To locally build your github page website for your github repository. This is in order to make and preview changes before pushing these to github.  
<br><br>

1. Uninstall Ruby (if installed)
2. Reinstall newest version of Ruby from [https://rubyinstaller.org.downloads/](https://rubyinstaller.org.downloads/)
3. Use Gitbash to download repo `git clone https://github.com/OtagoPolytechnic/DunedinIoT.git`
4. Move into the git repo ( `cd DunedinIoT`) and then run `gem install bundler`
5. If an error about **nokogori** package remove/delete the **Gemfile.lock** and rerun `gem install bundler`
6. Serve the page using `bundle exec Jekyll serve`
7. In a web browser go to `http://127.0.0.1:4000/DunedinIoT`