echo Converting cpp files...
for file in src/**.cpp; do
  iconv -f UTF-16 -t UTF-8 $file -o $file
done
echo Converting header files
for file in include/**.h; do
  iconv -f UTF-16 -t UTF-8 $file -o $file
done
