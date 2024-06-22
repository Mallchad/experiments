

local command = "bash -e files=(build/*) ; for x_executable in $files ; do; echo '$x_executable:           $($x_executable)' ; done | column --separator='   '"
