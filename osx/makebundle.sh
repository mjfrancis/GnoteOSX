#!/bin/bash

if [ -d Gnote.app ] && [ "$1x" = "-fx" ]; then
	rm -rf Gnote.app
fi

if [ ! -d Gnote.app ]; then
    gtk-mac-bundler Gnote.bundle
else
	echo "Note Gnote.app bundle already exists, only stripping it..."
fi

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

echo "Removing unnecessary files from bundle"
rm -rf Gnote.app/Contents/Resources/share/themes/Adwaita/gtk-2.0
rm -rf Gnote.app/Contents/Resources/share/themes/Default/gtk-2.0-key

# broken - causes crash
rm -f Gnote.app/Contents/Resources/lib/gnote/addins/3.9.0/notedirectorywatcher.*

echo "Installing gdk-pixbuf loader cache"
gdk-pixbuf-query-loaders | sed -e 's|.*\(/gdk-pixbuf-2.0/[^/]*/loaders/[^/]*\)$|"@executable_path/../Resources/lib\1|g' > Gnote.app/Contents/Resources/lib/gdk-pixbuf-2.0/2.10.0/loaders.cache

echo "Strip debug symbols from bundle binaries"
strip_binaries



