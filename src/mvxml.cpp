#include <fmt/core.h>
#include <fmt/color.h>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <filesystem>
#include <vector>
#include <optional>
#include <CLI/CLI.hpp>

std::optional<std::filesystem::path> find(std::filesystem::path file, const std::string &search);

int main(int argc, char *argv[])
{

    CLI::App app;

    std::filesystem::path destination;
    std::vector<std::filesystem::path> source;
    std::string name;

    app.add_option("-s,--source", source, "Source paths")->required();
    app.add_option("-d,--destination", destination, "Destination where file will go.")->required();
    app.add_option("-n,--name", name, "Name you want to find");

    CLI11_PARSE(app, argc, argv);

    auto option = std::filesystem::directory_options::skip_permission_denied;

    try
    {
        for (auto &path : source)
        {
            if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path))
            {
                fmt::print(stderr, fmt::fg(fmt::color::red) | fmt::emphasis::bold, " Error: {} is not a valid directory.\n", path.string());
                continue;
            }

            for (const auto &location : std::filesystem::recursive_directory_iterator(path, option))
            {
                if (!std::filesystem::is_directory(location))
                {
                    if (location.path().extension() == ".xml")
                    {
                        try
                        {
                            std::optional<std::filesystem::path> file_found = find(location.path(), name);
                            if (file_found.has_value())
                            {
                                std::filesystem::copy(file_found.value(), destination);
                            }
                        }
                        catch (const std::filesystem::filesystem_error &e)
                        {
                            fmt::print(stderr, fmt::fg(fmt::color::red) | fmt::emphasis::bold, "File System Error on {}: {}\n", location.path().string(), e.what());
                        }
                        catch (const std::exception &e)
                        {
                            fmt::print(stderr, fmt::fg(fmt::color::yellow), "Parse Error on {}: {}\n", location.path().string(), e.what());
                        }
                    }
                }
            }
        }
    }
    catch (std::filesystem::filesystem_error &e)
    {
        fmt::print(stderr, fmt::fg(fmt::color::red) | fmt::emphasis::bold, "File System Error: {}" , e.what());
    }
    catch (const std::exception &e)
    {
        fmt::print(stderr, fmt::fg(fmt::color::yellow), "Parse Error: {}\n", e.what());
    }

    return 0;
}

std::optional<std::filesystem::path> find(std::filesystem::path file, const std::string &search)
{
    rapidxml::file<> xmlfile(file.string().c_str());

    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlfile.data());

    rapidxml::xml_node<> *node = doc.first_node("channel");
    if (!node)
        return std::nullopt;
    rapidxml::xml_attribute<> *attr = node->first_attribute();
    if (!attr)
        return std::nullopt;

    if (std::string(attr->value()) == search)
        return file;

    return std::nullopt;
}