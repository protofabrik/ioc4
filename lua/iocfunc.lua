dofile("test.db")

-- Load database from lua DB table
function loadDB(db)
	for z,record in pairs(db) do
		--Check arguments
		if(record.name == Nil) then
			print("Mandatory field NAME is missing from record "..z)
			return;
		end

		if(record.type == Nil) then
			print("Mandatory field TYPE is missing from record "..record.name)
			return;
		end

		--print(record.name)
		-- Create record
		ioc.createRecord(record.name,record.type)

		-- Set all of the appropriate fields
		for fname,fval in pairs(record.fields) do
			--print(record.name.."."..fname.."::"..tostring(fval))

			--check if the field has a type, if it has we should try to create it first
			if(fname:find("__")) then
				type=fname:sub(fname:find("__")+2)
				fname=fname:sub(0,fname:find("__")-1)
				ioc.addStagingField(record.name.."."..fname,type)
			end

			ioc.setStagingField(record.name.."."..fname,tostring(fval))
		end

		-- Bind or init the record to a component
		if(record.bind) then
		 	ioc.bindRecord(record.name,record.bind)
		else
			ioc.initRecord(record.name)
		end

	end
end

-- Load links from table
function loadLinks(links)
	for z,link in pairs(links) do
		ioc.addLink(link.from,link.to,link.type,link.args)
	end
end


-- List records currently in the database
function dbl()
	for name in ioc.dbl() do
		print(name)
	end
end