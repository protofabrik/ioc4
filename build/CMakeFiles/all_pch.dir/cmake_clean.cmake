FILE(REMOVE_RECURSE
  "CMakeFiles/all_pch"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/all_pch.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
