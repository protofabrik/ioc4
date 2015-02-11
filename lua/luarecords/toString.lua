--evalute new format function
function init()
	if(record.fmt==Nil) then error("FMT FIELD IS MISSING!") end
	if(record.args==Nil) then error("ARGS FIELD IS MISSING!") end

	--print(record.fmt,record.args)
	formatting_function = string.format("record.value=string.format(%q,%s)",record.fmt,record.args)
	print("New formatting function "..formatting_function)
	format=loadstring(formatting_function)

	--Register argument handlers:
	-- Iterate over arguments string, and register each field
	for i in string.gmatch(record.args, "([^,]+)") do
		i=i:sub(8) --substring that removes 'record.'
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
