--Load ioc lua bindings
package.loadlib("../build/libioclua.so","init_lib")()
--Load pure lua ioc functions
dofile("iocfunc.lua")


ioc.init()
ioc.startPVAccess()

loadDB(db)
loadLinks(links)


function test_long_chain(n)
	--Generate 100 records
	db={}
	for i=1,n do
		rec={}
		rec.name = "TEST:AI"..i
		rec.type = "STRING"
		rec.fields = {value = i}

		table.insert(db,rec)
	end

	--Create a long chain of links
	links={}
	for i=1,n-1 do
		link={}
		link.from="TEST:AI"..i..".value"
		link.to="TEST:AI"..(i+1)..".value"
		link.type="PUT"
		link.args=""

		table.insert(links,link)
	end

	loadDB(db)
	loadLinks(links)
	
end

-- ioc.createRecord("LUA","DOUBLE")
-- ioc.setStagingField("LUA.A","213")
-- ioc.setStagingField("LUA.B","3.14")
-- ioc.setStagingField("LUA.code","print('hello from lua'");
-- ioc.bindRecord("LUA","STD::LUA")



-- Create a test scan record

-- ioc.createRecord("TEST:SCAN","STD::SCAN")
-- ioc.setStagingField("TEST:SCAN.rate","0.1")
-- ioc.bindRecord("TEST:SCAN","STD::SCAN")

-- ioc.createRecord("TEST1","STRING")
-- ioc.setStagingField("TEST1.value","Hello World!")
-- ioc.initRecord("TEST1")

