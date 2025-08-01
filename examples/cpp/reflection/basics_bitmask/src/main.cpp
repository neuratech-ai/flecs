#include <basics_bitmask.h>
#include <iostream>

struct Toppings : flecs::bitmask {
    static constexpr uint32_t Bacon = 0x1;
    static constexpr uint32_t Lettuce = 0x2;
    static constexpr uint32_t Tomato = 0x4;
};

struct Sandwich {
    uint32_t toppings;
};

int main(int, char *[]) {
    flecs::world ecs;

    // Register components with reflection data
    ecs.component<Toppings>()
        .bit("Bacon", Toppings::Bacon)
        .bit("Lettuce", Toppings::Lettuce)
        .bit("Tomato", Toppings::Tomato);

    ecs.component<Sandwich>()
        .member<Toppings>("toppings");

    // Create entity with Sandwich as usual
    flecs::entity e = ecs.entity()
        .set<Sandwich>({Toppings::Bacon | Toppings::Lettuce});

    // Convert Sandwich component to flecs expression string
    const Sandwich& c = e.get<Sandwich>();
    std::cout << ecs.to_expr(&c).c_str() << "\n"; // {toppings: Lettuce|Bacon}
}
