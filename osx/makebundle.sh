#!/bin/bash

function do_strip {
    tp=$(file -b --mime-type "$1")

    if [ "$tp" != "application/octet-stream" ]; then
        return
    fi

    name=$(mktemp -t bundle)
    st=$(stat -f %p "$1")
    
    strip -o "$name" -S "$1"
    mv -f "$name" "$1"

    chmod "$st" "$1"
    chmod u+w "$1"
}

function strip_binaries {

    for i in $(find -E Gnote.app/Contents/Resources -type f -regex '.*\.(so|dylib)$'); do
        do_strip "$i"
    done

    for i in $(find Gnote.app/Contents/Resources/bin -type f); do
        if [ -x "$i" ]; then
            do_strip "$i"
        fi
    done

    do_strip Gnote.app/Contents/MacOS/gnote-bin

}

function install_help_files_for_language {
    current="$PWD"
    target="Gnote.app/Contents/Resources/$2.lproj/Gnote.help"
    mkdir -p "$target"
    pushd "$PWD" > /dev/null
    cd "$target"
    yelp-build html "$current/../help/$1"
    # Fill in missing images from English
    mkdir -p figures
    cp -n $current/../help/C/figures/*.png figures/
    popd > /dev/null
    cp ../data/icons/hicolor_apps_16x16_gnote.png "Gnote.app/Contents/Resources/$2.lproj/Gnote.help/"
    sed -e 's/^<head>$/<head><meta name="AppleTitle" Content="Gnote Help"><meta name="AppleIcon" content="hicolor_apps_16x16_gnote.png">/g' -i "" "Gnote.app/Contents/Resources/$2.lproj/Gnote.help/index.html"
    hiutil -Cgf "Gnote.app/Contents/Resources/$2.lproj/Gnote.help/Gnote.helpindex" "Gnote.app/Contents/Resources/$2.lproj/Gnote.help"
}

function install_help_files {
    echo "Installing help files for en"
    install_help_files_for_language "C" "en"
    for l in $(find ../help -type d -maxdepth 1 -not -name C -not -name help | sed -e "s#^.*/##g"); do
        echo "Installing help files for $l"
        install_help_files_for_language "$l" "$l"
    done
}



if [ -d Gnote.app ] && [ "$1x" = "-fx" ]; then
	rm -rf Gnote.app
fi

if [ ! -d Gnote.app ]; then
    gtk-mac-bundler Gnote.bundle

    echo "Removing unnecessary files from bundle"
    rm -rf Gnote.app/Contents/Resources/share/themes/Adwaita/gtk-2.0
    rm -rf Gnote.app/Contents/Resources/share/themes/Default/gtk-2.0-key

    echo "Installing gdk-pixbuf loader cache"
    gdk-pixbuf-query-loaders | sed -e 's|.*\(/gdk-pixbuf-2.0/[^/]*/loaders/[^/]*\)$|"@executable_path/../Resources/lib\1|g' > Gnote.app/Contents/Resources/lib/gdk-pixbuf-2.0/2.10.0/loaders.cache

    echo "Installing input method cache"
    gtk-query-immodules-3.0 | sed -e 's|.*\(/lib/gtk-.*/immodules/.*\)|"@executable_path/../Resources\1|g' -e 's|"[^"]*locale"|"@executable_path/../Resources/share/locale"|g' > Gnote.app/Contents/Resources/lib/gtk-3.0/3.0.0/immodules.cache

    echo "Installing help files"
    install_help_files

else
	echo "Note Gnote.app bundle already exists, only stripping it..."
fi

echo "Strip debug symbols from bundle binaries"
strip_binaries



