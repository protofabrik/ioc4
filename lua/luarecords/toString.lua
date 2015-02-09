--evalute new format function
function init()
	if(fmt==Nil) then error("FMT FIELD IS MISSING!") end
	if(args==Nil) then error("ARGS FIELD IS MISSING!") end

	print(fmt,args)
	formatting_function = string.format("value=string.format(%q,%s)",fmt,args)
	print("New formatting function "..formatting_function)
	format=loadstring(formatting_function)

	--Register argument handlers:
	-- Iterate over arguments string, and register each field
	for i in string.gmatch(args, "([^,]+)") do
		print(i.."_=format")
		loadstring(i.."_=format")()
	end
end

--re-evaluate format string
function fmt_()
	init()
end

function args_()
	init()
end
