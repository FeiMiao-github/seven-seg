#ifndef LOGIC_H__
#define LOGIC_H__

#include <memory>

namespace logic
{
    class op_base;
    class out_port;

    class port_base
    {
    public:
        port_base(op_base &op)
            : op(&op)
        {
        }

        virtual bool get_value() const = 0;

    protected:
        op_base *get_op() const
        {
            return this->op;
        }

    private:
        op_base *op;
    };

    class op_base
    {
    public:
        virtual bool get_value() const = 0;
    };

    class in_port : public port_base, std::enable_shared_from_this<in_port>
    {
    public:
        in_port(op_base &op)
            : port_base(op)
        {
        }

        void link(std::shared_ptr<out_port> &out)
        {
            this->out = out;
        }

        bool get_value() const override;

    private:
        std::weak_ptr<out_port> out;
    };

    class out_port : public port_base, std::enable_shared_from_this<out_port>
    {
    public:
        out_port(op_base &op)
            : port_base(op)
        {
        }

        bool get_value() const override
        {
            return this->get_op()->get_value();
        }
    };

    class op_in : public op_base
    {
    public:
        op_in()
        {
            this->out = std::make_shared<out_port>(*this);
        }

        virtual void set_value(bool value)
        {
            this->value = value;
        }

        virtual bool get_value() const override
        {
            return this->value;
        }

        void link(std::shared_ptr<in_port> &in)
        {
            in->link(this->out);
        }

        std::shared_ptr<out_port>& get_out()
        {
            return out;
        }

    private:
        bool value;

        std::shared_ptr<out_port> out;
    };

    class op_out : public op_base
    {
    public:
        op_out()
        {
            this->in = std::make_shared<in_port>(*this);
        }

        virtual bool get_value() const override
        {
            return this->in->get_value();
        }

        void link(std::shared_ptr<out_port> &out)
        {
            this->in->link(out);
        }

        std::shared_ptr<in_port>& get_in()
        {
            return in;
        }

    private:
        std::shared_ptr<in_port> in;
    };

    class op_not : public op_base
    {
    public:
        op_not()
        {
            this->in = std::make_shared<in_port>(*this);
            this->out = std::make_shared<out_port>(*this);
        }

        virtual bool get_value() const override
        {
            return !this->in->get_value();
        }

        void link(std::shared_ptr<out_port> &out)
        {
            this->in->link(out);
        }

        void link(std::shared_ptr<in_port> &in)
        {
            in->link(this->out);
        }

        std::shared_ptr<in_port>& get_in()
        {
            return in;
        }

        std::shared_ptr<out_port>& get_out()
        {
            return out;
        }

    private:
        std::shared_ptr<in_port> in;

        std::shared_ptr<out_port> out;
    };

    template <int N_IN = 2>
    class op_and : public op_base
    {
    public:
        op_and()
        {
            for(int i = 0; i < N_IN; i++)
            {
                this->in[i] = std::make_shared<in_port>(*this);
            }
            this->out = std::make_shared<out_port>(*this);
        }

        bool get_value() const override
        {
            bool ret = true;
            for (int i = 0; i < N_IN; i++)
            {
                ret = ret && this->in[i]->get_value();
            }
            return ret;
        }

        template <int Index>
        void link(std::shared_ptr<out_port> &out)
        {
            this->in[Index]->link(out);
        }

        void link(std::shared_ptr<in_port> &in)
        {
            in->link(this->out);
        }

        template <int Index>
        std::shared_ptr<in_port>& get_in()
        {
            static_assert(Index >= 0 && Index < N_IN, "Index out of range");
            return in[Index];
        }

        std::shared_ptr<out_port>& get_out()
        {
            return out;
        }

    private:
        std::shared_ptr<in_port> in[N_IN];

        std::shared_ptr<out_port> out;
    };

    template <int N_IN = 2>
    class op_or : public op_base
    {
    public:
        op_or()
        {
            for (int i = 0; i < N_IN; i++)
            {
                this->in[i] = std::make_shared<in_port>(*this);
            }
            
            this->out = std::make_shared<out_port>(*this);
        }

        virtual bool get_value() const override
        {
            bool ret = false;
            for (int i = 0; i < N_IN; i++)
            {
                ret = ret || this->in[i]->get_value();
            }
            return ret;
        }

        template <int Index>
        void link(std::shared_ptr<out_port> &out)
        {
            static_assert(Index >= 0 && Index < N_IN, "Index out of range");
            this->in[Index]->link(out);
        }

        void link(std::shared_ptr<in_port> &in)
        {
            in->link(this->out);
        }

        template <int Index>
        std::shared_ptr<in_port>& get_in0()
        {
            static_assert(Index >= 0 && Index < N_IN, "Index out of range");
            return in[Index];
        }

        std::shared_ptr<out_port>& get_out()
        {
            return out;
        }

    private:
        std::shared_ptr<in_port> in[N_IN];

        std::shared_ptr<out_port> out;
    };
}

#endif // LOGIC_H__
