#pragma once

// std
#include <list>
#include <functional>

namespace callisto::framework
{
#pragma region helpers

template<typename _connections_place_type>
class raii_connection
{
private:
    using connections_place_type = _connections_place_type;

    using connection_type = typename connections_place_type::iterator;

    connections_place_type& connections;

    connection_type connection;

    bool has_connection = false;

    void move_from(raii_connection&& connection)
    {
        this->connections    = connection.connections;
        this->connection     = connection.connection;
        this->has_connection = connection.has_connection;

        connection.has_connection = false;
    }

public:
    raii_connection(
        connections_place_type& connections, 
        connection_type& connection
    ) : connections(connections), connection(connection)
    {
        this->has_connection = true;
    }

    raii_connection(
        raii_connection&& connection
    )
    {
        this->move_from(std::move(connection));
    }

    ~raii_connection()
    {
        if(this->has_connection)
        {
            disconnect();
        }
    }

    inline void disconnect()
    {
        this->connections.erase(this->connection);
        this->has_connection = false;
    }

    raii_connection& operator=(raii_connection&& connection)
    {
        this->move_from(std::move(connection));
    }

};

template<typename _connections_place_type>
class signal_connection
{
private:
    using connections_place_type = _connections_place_type;

    using connection_type = typename connections_place_type::iterator;

    using raii_connection_type = raii_connection<_connections_place_type>;

    connections_place_type& connections;

    connection_type connection;

public:
    signal_connection(
        connections_place_type& connections, 
        connection_type& connection
    ) : connections(connections), connection(connection)
    {
        
    }

    void disconnect()
    {
        this->connections.erase(this->connection);
    }

    raii_connection_type to_raii()
    {
        return raii_connection_type(this->connections, this->connection);
    }
};

#pragma endregion

template<typename _func_type>
class signal
{
    using func_type = _func_type;

    using connections_place_type = std::list<std::function<func_type>>;

    using connection_type = signal_connection<connections_place_type>;

    connections_place_type connections;

public:
    signal() { };

    connection_type connect(func_type& func)
    {
        std::function functor(func);

        this->connections.push_back(std::move(functor));
        auto connection = --(connections.end());

        return connection_type(this->connections, connection);
    }

    connection_type connect(std::function<func_type>& func)
    {
        connections.push_back(func);
        auto connection = --(connections.end());

        return connection_type(this->connections, connection);
    }

    connection_type connect(std::function<func_type>&& func)
    {
        this->connections.push_back(std::move(func));
        auto connection = --(connections.end());

        return connection_type(this->connections, connection);
    }


    void disconnect(connection_type& connection)
    {
        connection.disconnect();
    }

    template<typename ...variable_params>
    void operator()(variable_params&&... params)
    {
        for(auto& connection : connections)
        {
            connection(std::forward<variable_params>(params)...);
        }
    }
};

}