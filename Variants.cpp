#include <iostream>
#include <variant>

using namespace std;
struct Params
{
    Params() = default;
    int a;
    int b;
};

class Top{
    public:

    explicit Top(int j, Params& p) : params{std::ref(p)} {}
    // Top() = default;
    Top(const Top&) = default;
    Top& operator=(const Top&) = default;
    Top(Top&&) = default;
    Top& operator=(Top&&) = default;
    ~Top() = default;

    void updateStruct(Params& p_)
    {
        /*printf("\nUpdate struct - TOP\n");
        printf("p_.a: %u, params.a: %u\n", p_.a, params.a);
        printf("p_.b: %u, params.b: %u\n", p_.b, params.b);
        params = p_;
        printf("Params.a: %u\n", params.a);
        printf("Params.a: %u\n", params.b);*/
    }

    int get() {return i;};
    void set(int& i) {i = 60;};
    private:
    int i = 1;
    
    private:
    // Params& params;
    std::reference_wrapper<Params> params;
    
};

class Bottom{
    public:
    explicit Bottom(int j, Params& p) : params{std::ref(p)} {}
    /*explicit Bottom(int j, Params& p)
    {
        printf("\nHere in Bottom Const\n");
        i = j;
        params = p;
        
    }*/
    // Bottom() = default;
    Bottom(const Bottom&) = default;
    Bottom& operator=(const Bottom&) = default;
    Bottom(Bottom&&) = default;
    Bottom& operator=(Bottom&&) = default;
    ~Bottom() = default;

    void updateStruct(Params& p_)
    {
        /*printf("\nUpdate struct - BOTTOM\n");
        printf("p_.a: %u, params.a: %u\n", p_.a, params.a);
        printf("p_.b: %u, params.b: %u\n", p_.b, params.b);
        params = p_;
        printf("Params.a: %u\n", params.a);
        printf("Params.a: %u\n", params.b);
        params.a = 220;
        params.b = 221;*/
    }
    int i = 2;
    int get() {return i;};
    void set(int& i) {i = 50;};
    
    private:
    // Params& params;
    std::reference_wrapper<Params> params;
};

using Type = std::variant<Top, Bottom>;

class Base
{
    public:
    // Base() = default;

    Base(int i);
    
    Base(const Base&) = delete;
    Base& operator=(const Base&) = delete;
    Base(Base&&) = delete;
    Base& operator=(Base&&) = delete;
    ~Base() = default;
    
    int k;
    Type type{Top{1, params}};
    Type getTypeTop()
    {
        return Type{std::in_place_type<Top>, 1, params};
    }
    
    Type getTypeBottom()
    {
        return Type{std::in_place_type<Bottom>, 1, params};
    }

    private:
    // Params params;
    std::reference_wrapper<Params> params;
};

Base::Base(int i)
{
    if(i)
    {
        type = getTypeTop();
    }
    else
    {
        type = getTypeBottom();
    }
}

int main()
{
    Base base{1};
    Params p;
    // std::reference_wrapper<Params> p;
    p.a = 101;
    p.b = 102;
    base.type = Type{std::in_place_type<Top>, 5, p};
    auto lambda{
    [&](auto& policy) 
    {
        printf("\ntype.i: %d\n", policy.get()); 
        policy.set(base.k);
        printf("\ntype.k: %d\n", base.k); 
        policy.updateStruct(p);
        return policy.get();
    }
    };
    auto res = std::visit(lambda, base.type);
    printf("\nres: %d\n", res); 
    printf("\nk: %d\n", base.k); 

}
