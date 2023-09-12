add_syslinks("pthread","gxiapi")


includes("Share")

target("CV")
    set_kind("binary")
    set_rules("mode.debug", "mode.release")
     
    add_includedirs("include")
    add_files("src/*.cpp")
    add_packages("opencv")
