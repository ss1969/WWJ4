local TARGET_NAME = os.scriptdir():match(".+[/\\]([%w_]+)")
project_dir = os.scriptdir()
project_name = project_dir:match(".+[/\\]([%w_]+)")

csdk_root = "../../luatos-soc-2024/" --csdk根目录,可自行修改
includes(csdk_root.."csdk.lua")
description_common()

target(project_name,function()
    set_kind("static")
    set_targetdir("$(buildir)/".. project_name .. "/")
    description_csdk()
    set_warnings("error")

    -- ota settings
    local chip_target = nil
    if has_config("chip_target") then chip_target = get_config("chip_target") end
    -- 程序区缩小到1b7000，剩余2c2000 - 1b7000 = 10b000
    if chip_target == "ec718p" or chip_target == "ec718pm" or chip_target == "ec716e" or chip_target == "ec718e" then
        add_defines("AP_FLASH_LOAD_SIZE=0x1b7000",{public = true})
        add_defines("AP_PKGIMG_LIMIT_SIZE=0x1b7000",{public = true})
        add_defines("FULL_OTA_SAVE_ADDR=0x235000",{public = true})
    end
	if chip_target == "ec718u" or chip_target == "ec718um" or chip_target == "ec718hm" then
        add_defines("AP_FLASH_LOAD_SIZE=0x40b000",{public = true})
        add_defines("AP_PKGIMG_LIMIT_SIZE=0x40b000",{public = true})
        add_defines("FULL_OTA_SAVE_ADDR=0x49C000",{public = true})
    end

    --加入代码和头文件
    add_includedirs("./inc",{public = true})
    add_files("./src/*.c",{public = true})

    --fskv
    add_includedirs(luatos_root.."/components/fskv", {public = true})
    add_files(luatos_root.."/components/fskv/*.c")
    remove_files(luatos_root.."/components/fskv/luat_lib_fskv.c")
    --http
    add_includedirs(luatos_root.."/components/network/libhttp", {public = true})
    add_includedirs(luatos_root.."/components/network/http_parser", {public = true})
    add_files(luatos_root.."/components/network/libhttp/*.c")
    remove_files(luatos_root.."/components/network/libhttp/luat_lib_http.c")
    add_files(luatos_root.."/components/network/http_parser/*.c")


end)