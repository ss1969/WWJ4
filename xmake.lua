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
        add_defines("AP_FLASH_LOAD_SIZE=0x200000",{public = true})
        add_defines("AP_PKGIMG_LIMIT_SIZE=0x200000",{public = true})
        add_defines("FULL_OTA_SAVE_ADDR=0x270000",{public = true})
    end
	if chip_target == "ec718u" or chip_target == "ec718um" or chip_target == "ec718hm" then
        add_defines("AP_FLASH_LOAD_SIZE=0x40b000",{public = true})
        add_defines("AP_PKGIMG_LIMIT_SIZE=0x40b000",{public = true})
        add_defines("FULL_OTA_SAVE_ADDR=0x49C000",{public = true})
    end

    --加入代码和头文件
    add_includedirs(project_dir .. "./inc",{public = true})
    add_files(project_dir .. "./src/*.c",{public = true})
    --lvgl9
    add_includedirs(project_dir .. "./src/lvgl9")
    add_files(project_dir .. "./src/lvgl9/**.c")
    remove_files(project_dir .. "./src/lvgl9/demos/**")
    remove_files(project_dir .. "./src/lvgl9/examples/**")
    remove_files(project_dir .. "./src/lvgl9/src/draw/nxp/**")
    remove_files(project_dir .. "./src/lvgl9/src/draw/renesas/**")
    remove_files(project_dir .. "./src/lvgl9/src/draw/sdl/**")
    remove_files(project_dir .. "./src/lvgl9/src/drivers/**")
    --gui guider
    add_files(project_dir .. "./src/ui/**.c")
    add_includedirs(project_dir .. "./src/ui")
    add_includedirs(project_dir .. "./src/ui/custom")
    add_includedirs(project_dir .. "./src/ui/guider_fonts")
    add_includedirs(project_dir .. "./src/ui/guider_customer_fonts")

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
    --cjson
    add_includedirs(luatos_root .. "/components/cjson")
    add_files(luatos_root.."/components/cjson/*.c")
    --mqtt
    add_includedirs(luatos_root.."/components/network/libemqtt", {public = true})
    add_files(luatos_root.."/components/network/libemqtt/*.c")
    remove_files(luatos_root.."/components/network/libemqtt/luat_lib_mqtt.c")
    --lcd
    -- add_includedirs(luatos_root.."/components/u8g2", {public = true})
    add_includedirs(luatos_root.."/components/lcd", {public = true})
    add_files(luatos_root.."/components/lcd/*.c")
    remove_files(luatos_root.."/components/lcd/luat_lib_lcd.c")
end)